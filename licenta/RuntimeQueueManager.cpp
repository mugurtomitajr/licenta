//
//  RuntimeQueueManager.cpp
//  practice
//

#include "RuntimeQueueManager.hpp"

RuntimeQueueManager::RuntimeQueueManager() {
    this -> _instancesToAdd = std::queue<InstanceQueueData>();
    this -> _instancesToRemove = std::queue<InstanceQueueData>();
}

RuntimeQueueManager::~RuntimeQueueManager() {
    this -> _clear();
}

void RuntimeQueueManager::AddInstance(std::string p_id, std::string p_shaderId, void *p_reference) {
    RuntimeQueueManager::InstanceQueueData entry;
    entry._id = p_id;
    entry._shaderId = p_shaderId;
    entry._reference = p_reference;
    this -> _instancesToAdd.push(entry);
}

void RuntimeQueueManager::RemoveInstance(std::string p_id, void *p_reference, bool p_deleteModel) {
    RuntimeQueueManager::InstanceQueueData entry;
    entry._id = p_id;
    entry._reference = p_reference;
    entry._deleteModel = p_deleteModel;
    this -> _instancesToRemove.push(entry);
}

void RuntimeQueueManager::_clear() {
    this -> _instancesToAdd = std::queue<InstanceQueueData>();
    this -> _instancesToRemove = std::queue<InstanceQueueData>();
}
