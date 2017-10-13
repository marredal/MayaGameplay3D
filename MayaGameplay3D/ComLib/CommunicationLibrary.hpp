#pragma once
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <mutex>
enum ProgramType {
    MAYA,
    GAMEPLAY,
    DUMMY
};

enum Node {
    CAMERA,
    LIGHT,
    MESH,
    MATERIAL,
    TRANSFORMATION
};

struct MayaInformation {
    float translation[3];
    ProgramType type;

};

class CommunicationLibrary {

public:
    // Empty constructor.
    CommunicationLibrary();

    virtual ~CommunicationLibrary();

    // Initialize the communication library.
    void Init(ProgramType type, size_t bufferSize);
    // Send information to the shared buffer.
    bool Send(MayaInformation *mayaData);
    // Read information from the shared buffer.
    bool Receive();
    // Check if there is room for the next message that is going to be sent.
    bool NextSize();

private:
    size_t* m_head;
    size_t* m_tail;
    size_t* m_freeMemory;
    size_t m_bufferSize;
    char* m_buffer;
    TCHAR* m_mapName = TEXT("MayaGameplayFilemapOBJ");
    MayaInformation m_MayaData;
    HANDLE m_filemapHandle;
    HANDLE m_mutex;
    DWORD ms = INFINITE;
    

};

