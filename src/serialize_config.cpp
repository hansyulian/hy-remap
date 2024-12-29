#include "serialize_config.h"

// Define how to deserialize the JSON into the Trigger struct
void from_json(const json& j, Trigger& t) {
    j.at("id").get_to(t.id);
    j.at("name").get_to(t.name);
}

// Define how to deserialize the JSON into the Action struct
void from_json(const json& j, Action& a) {
    j.at("id").get_to(a.id);
    j.at("name").get_to(a.name);
    j.at("type").get_to(a.type);
    j.at("keys").get_to(a.keys);  // Assuming 'keys' is a list of strings
}

// Define how to deserialize the JSON into the Mapping struct
void from_json(const json& j, Mapping& m) {
    j.at("triggerId").get_to(m.triggerId);
    j.at("actionId").get_to(m.actionId);
}

// Define how to deserialize the JSON into the Profile struct
void from_json(const json& j, Profile& p) {
    j.at("name").get_to(p.name);
    
    if (j.contains("programNames")) {
        j.at("programNames").get_to(p.programNames);
    }

    if (j.contains("mapping")) {
        j.at("mapping").get_to(p.mapping);
    }
}

// Define how to deserialize the JSON into the Config struct
void from_json(const json& j, Config& c) {
    j.at("triggers").get_to(c.triggers);
    j.at("actions").get_to(c.actions);
    j.at("profiles").get_to(c.profiles);
}
