#pragma once

enum ProgramType {
    MAYA,
    GAMEPLAY
};

struct MayaInformation {
    float translation[3];
};

class CommunicationLibrary
{

public:
    // Empty constructor.
    CommunicationLibrary();

    virtual ~CommunicationLibrary();

    // Initialize the communication library.
    void Init(ProgramType, size_t bufferSize);
    // Send information to the shared buffer.
    void Send();
    // Read information from the shared buffer.
    void Receive();
    // Check if there is room for the next message that is going to be sent.
    bool NextSize();

private:
    size_t* m_head;
    size_t* m_tail;
    size_t* m_freeMemory;
    size_t m_bufferSize;
    char* m_buffer;
    MayaInformation m_MayaData;

};

