
#include "maya_includes.h"
#include <iostream>
#include "CommunicationLibrary.cpp"

using namespace std;

CommunicationLibrary comLib;
MCallbackIdArray callbackIdArray;
MStatus status = MS::kSuccess;

void nodeAdded(MObject &node, void * clientData) {

    MGlobal::displayInfo("Node Created.");
    MGlobal::displayInfo(node.apiTypeStr());

    if (node.apiType() == MFn::kMesh || node.apiType() == MFn::kTransform) {
        MeshStruct *sendMesh;
        if (node.apiType() == MFn::kTransform) {
            MFnTransform tempTransform(node);
            MFloatMatrix;

            for (int i = 0; i < 4; i++) {
                sendMesh->transformation[i][0] = tempTransform.transformation().asMatrix().matrix[i][0];
                for (int j = 0; j < 4; j++)
                    sendMesh->transformation[i][j] = tempTransform.transformation().asMatrix().matrix[i][j];
            }

        }
        comLib.Send(sendMesh);
    }
}

// called when the plugin is loaded
EXPORT MStatus initializePlugin(MObject obj) {
    // most functions will use this variable to indicate for errors
    MStatus res = MS::kSuccess;

    MFnPlugin myPlugin(obj, "Maya plugin", "1.0", "Any", &res);
    if (MFAIL(res)) {
        CHECK_MSTATUS(res);
    }

    MGlobal::displayInfo("Maya plugin loaded!");

    comLib.Init(MAYA);

    MCallbackId addNodeID = MDGMessage::addNodeAddedCallback(nodeAdded, "dependNode", NULL, &status);

    // if res == kSuccess then the plugin has been loaded,
    // otherwise is has not.

    if (status == MS::kSuccess)
        if (callbackIdArray.append(addNodeID) == MS::kSuccess);

    return res;

}


EXPORT MStatus uninitializePlugin(MObject obj) {

    MFnPlugin plugin(obj);

    MGlobal::displayInfo("Maya plugin unloaded!");
    MMessage::removeCallbacks(callbackIdArray);

    return MS::kSuccess;
}