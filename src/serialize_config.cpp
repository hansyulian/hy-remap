#include "main.h"

// Define how to deserialize the JSON into the Trigger struct
void from_json(const json& j, Trigger& t) {
    j.at("id").get_to(t.id);
    j.at("name").get_to(t.name);
    j.at("key").get_to(t.key);
}

// Define how to deserialize the JSON into the Action struct
void from_json(const json& j, Action& a) {
    j.at("id").get_to(a.id);
    j.at("name").get_to(a.name);
    j.at("keys").get_to(a.keys);  // Assuming 'keys' is a list of strings
    
    a.type = ActionType::SIMPLE;
    string typeValue = j.at("type").get<string>();
    if (typeValue == "simple"){        
        a.type = ActionType::SIMPLE;
    }
}

// Define how to deserialize the JSON into the Mapping struct
void from_json(const json& j, Mapping& m) {
    j.at("triggerId").get_to(m.triggerId);
    j.at("actionId").get_to(m.actionId);
}

// Define how to deserialize the JSON into the Profile struct
void from_json(const json& j, Profile& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);

    // Set programNames to an empty vector if not defined
    if (j.contains("programNames")) {
        j.at("programNames").get_to(p.programNames);
    } else {
        p.programNames = {}; // Assign an empty vector
    }

    // Set mapping to an empty vector if not defined
    if (j.contains("mapping")) {
        j.at("mapping").get_to(p.mapping);
    } else {
        p.mapping = {}; // Assign an empty vector
    }
}

// Define how to deserialize the JSON into the Config struct
void from_json(const json& j, Config& c) {
    j.at("triggers").get_to(c.triggers);
    j.at("actions").get_to(c.actions);
    j.at("profiles").get_to(c.profiles);
    j.at("defaultProfileId").get_to(c.defaultProfileId);
}
