#include "CommunicationLibrary.hpp"



CommunicationLibrary::CommunicationLibrary() {
}


CommunicationLibrary::~CommunicationLibrary() {

    UnmapViewOfFile(m_buffer);
    CloseHandle(m_filemapHandle);
}

void CommunicationLibrary::Init(ProgramType type) {

    m_bufferSize = 100 * 1 << 20;
    size_t offset = sizeof(size_t*) * 3;

    m_filemapHandle = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        m_bufferSize + offset,
        m_mapName);

    if (m_mapName == NULL) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
    }

    m_buffer = (char*)MapViewOfFile(m_filemapHandle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        m_bufferSize + offset);

    if (m_buffer == NULL) {

        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(m_filemapHandle);
    }

    m_head = (size_t*)(m_buffer + m_bufferSize);
    m_tail = (size_t*)(m_buffer + m_bufferSize) + sizeof(size_t);
    m_freeMemory = (size_t*)(m_buffer + m_bufferSize) + 2 * sizeof(size_t);

    if (type == MAYA) {
        *m_head = 0;
        *m_tail = 0;
        *m_freeMemory = m_bufferSize;
    }
}

bool CommunicationLibrary::Send(MeshStruct *mayadata) {

    m_mutex = CreateMutex(nullptr, false, L"mutexObject");
    WaitForSingleObject(m_mutex, ms);
    // COPY mayadata to m_Mayadata
    bool status;

    if (!NextSize()) {
        m_meshData.type == DUMMY;
        memcpy((char*)m_buffer + *m_head, mayadata, sizeof(MeshStruct));
        *m_freeMemory = m_bufferSize - *m_head;
        if (*m_head == *m_tail)
            *m_head = 0;
        status = false;
    }

    else {
        m_meshData.type == MAYA;
        memcpy((char*)m_buffer + *m_head, mayadata, sizeof(MeshStruct));
        *m_head += sizeof(MeshStruct);
        *m_freeMemory -= sizeof(MeshStruct);
        status = true;
    }

    ReleaseMutex(m_mutex);
    return status;
}

bool CommunicationLibrary::Receive() {

    m_mutex = CreateMutex(nullptr, false, L"mutexObject");
    WaitForSingleObject(m_mutex, ms);

    bool status;

    memcpy(&m_meshData, (char*)m_buffer + *m_tail, sizeof(MeshStruct));

    if (m_meshData.type == MAYA) {
        *m_tail += sizeof(MeshStruct);
        *m_freeMemory += sizeof(MeshStruct);
        status = true;
    }

    if (m_meshData.type != MAYA) {

        if (*m_tail > *m_head) {
            *m_tail = 0;
            *m_freeMemory = m_bufferSize;
            status = false;
        }
    }

    ReleaseMutex(m_mutex);
    return status;
}

bool CommunicationLibrary::NextSize() {

    int bufferOffset = 64;
    if (m_bufferSize <= *m_head + sizeof(MeshStruct) + bufferOffset)
        return false;
    else
        return true;
}

MeshStruct CommunicationLibrary::GetMesh() {
    return m_meshData;
}
