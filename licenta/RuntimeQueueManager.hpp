//
//  RuntimeQueueManager.hpp
//  practice
//

#ifndef RuntimeQueueManager_hpp
#define RuntimeQueueManager_hpp

#include <cstdio>
#include <queue>
#include <string>

class RuntimeQueueManager {
public:
    RuntimeQueueManager();
    ~RuntimeQueueManager();
    struct InstanceQueueData {
        std::string _id = "";
        std::string _shaderId = "default";
        void *_reference = nullptr;
        bool _deleteModel = false;
    };
    
    std::queue<InstanceQueueData> _instancesToAdd = std::queue<InstanceQueueData>();
    std::queue<InstanceQueueData> _instancesToRemove = std::queue<InstanceQueueData>();
    
    void AddInstance(std::string p_id, std::string p_shaderId, void *p_reference);
    void RemoveInstance(std::string p_id, void *p_reference, bool p_deleteModel);
    
private:
    void _clear();
};

#endif /* RuntimeQueueManager_hpp */
