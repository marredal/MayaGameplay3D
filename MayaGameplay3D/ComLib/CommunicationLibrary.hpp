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


enum MayaNode {
    CAMERA,
    LIGHT,
    MESH,
    MATERIAL,
    TRANSFORMATION,
    NROFNODES
};

struct vec3 {
    float x;
    float y;
    float z;
};

struct vec2 {
    float U;
    float V;
};

struct MeshStruct {

    ProgramType type;
    double transformation[4][4];
    vec3 vertex;
    vec3 normal;
    vec2 texture;
    std::string name;
};

class CommunicationLibrary {

public:
    // Empty constructor.
    CommunicationLibrary();

    virtual ~CommunicationLibrary();

    // Initialize the communication library.
    void Init(ProgramType type);
    // Send information to the shared buffer.
    bool Send(MeshStruct *mayaData);
    // Read information from the shared buffer.
    bool Receive();
    // Check if there is room for the next message that is going to be sent.
    bool NextSize();
    MeshStruct GetMesh();

private:
    size_t* m_head;
    size_t* m_tail;
    size_t* m_freeMemory;
    size_t m_bufferSize;
    char* m_buffer;
    TCHAR* m_mapName = TEXT("MayaGameplayFilemapOBJ");
    MeshStruct m_meshData;
    HANDLE m_filemapHandle;
    HANDLE m_mutex;
    DWORD ms = INFINITE;


};

