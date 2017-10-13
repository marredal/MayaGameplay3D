#include "CommunicationLibrary.hpp"



CommunicationLibrary::CommunicationLibrary() {
}


CommunicationLibrary::~CommunicationLibrary() {

    UnmapViewOfFile(m_buffer);
    CloseHandle(m_filemapHandle);
}

void CommunicationLibrary::Init(ProgramType type, size_t bufferSize) {

    m_bufferSize = bufferSize;
    size_t offset = sizeof(size_t*) * 3;

    m_filemapHandle = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        bufferSize + offset,
        m_mapName);

    if (m_mapName == NULL) {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
    }

    m_buffer = (char*)MapViewOfFile(m_filemapHandle,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        bufferSize + offset);

    if (m_buffer == NULL) {

        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(m_filemapHandle);
    }

    m_head = (size_t*)(m_buffer + bufferSize);
    m_tail = (size_t*)(m_buffer + bufferSize) + sizeof(size_t);
    m_freeMemory = (size_t*)(m_buffer + bufferSize) + 2 * sizeof(size_t);

    if (type == MAYA) {
        *m_head = 0;
        *m_tail = 0;
        *m_freeMemory = bufferSize;
    }
}

bool CommunicationLibrary::Send(MayaInformation *mayadata) {

    m_mutex = CreateMutex(nullptr, false, L"mutexObject");
    WaitForSingleObject(m_mutex, ms);

    bool status;

    if (!NextSize()) {
        m_MayaData.type == DUMMY;
        memcpy((char*)m_buffer + *m_head, mayadata, sizeof(MayaInformation));
        *m_freeMemory = m_bufferSize - *m_head;
        if (*m_head == *m_tail)
            *m_head = 0;
        status = false;
    }

    else {
        m_MayaData.type == MAYA;
        memcpy((char*)m_buffer + *m_head, mayadata, sizeof(MayaInformation));
        *m_head += sizeof(MayaInformation);
        *m_freeMemory -= sizeof(MayaInformation);
        status = true;
    }

    ReleaseMutex(m_mutex);
    return status;
}

bool CommunicationLibrary::Receive() {

    m_mutex = CreateMutex(nullptr, false, L"mutexObject");
    WaitForSingleObject(m_mutex, ms);

    bool status;

    memcpy(&m_MayaData, (char*)m_buffer + *m_tail, sizeof(MayaInformation));

    if (m_MayaData.type == MAYA) {
        *m_tail += sizeof(MayaInformation);
        *m_freeMemory += sizeof(MayaInformation);
        status = true;
    }

    if (m_MayaData.type != MAYA) {

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
    if (m_bufferSize <= *m_head + sizeof(MayaInformation) + bufferOffset)
        return false;
    else
        return true;
}
