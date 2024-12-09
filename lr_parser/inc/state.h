#include "typedefs.h"
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

class State{

public:
  uint8_t idx = 0;
  uint8_t grammarIdx = 0;
  uint64_t id = 0;
  std::vector<item_t> items;
  State(const std::vector<item_t> it): items(it){}
  State(int size){ items.reserve(size);}
  State(){ items.reserve(20);}

  bool operator==(const State& other) const {
      return id == other.id && items == other.items;
  }
};

namespace std {
    template<>
    struct hash<production_t> {
        std::size_t operator()(const production_t& obj) const {
            std::size_t hash_value = std::hash<std::string>()(obj.lhs);

            for (const auto& str : obj.rhs) {
                hash_value ^= std::hash<std::string>()(str) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }
            return hash_value;
        }
    };
}
namespace std {
    template<>
    struct hash<item_t> {
        std::size_t operator()(const item_t& obj) const {
            std::size_t hash_value = std::hash<uint64_t>()(obj.dotPos);

            for (const auto& str : obj.lookAhead) {
                hash_value ^= std::hash<std::string>()(str) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }

            hash_value ^= std::hash<production_t>()(obj.production);

            return hash_value;
        }
    };
}

namespace std {
    template<>
    struct hash<State> {
        std::size_t operator()(const State& obj) const {
            std::size_t hash_value = std::hash<uint64_t>()(obj.id);

            for (const auto& item : obj.items) {
                hash_value ^= std::hash<item_t>()(item) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }

            return hash_value;
        }
    };
}

