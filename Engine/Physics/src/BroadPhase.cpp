#include "Primitive/Physics/BroadPhase.hpp"

#include "Primitive/Physics/Bounds.hpp"

namespace primitive
{
    std::vector<BroadPhasePair> BroadPhase::ComputePairs(const std::vector<BroadPhaseProxy>& proxies) const
    {
        std::vector<BroadPhasePair> pairs;

        for(std::size_t i = 0; i < proxies.size(); i++)
        {
            for(std::size_t j = i + 1; j < proxies.size(); j++)
            {
                const auto& first = proxies[i];
                const auto& second = proxies[j];

                if(first.entityID == second.entityID) { continue;}
                if(!first.bounds.Intercects(second.bounds)){ continue;}

                pairs.push_back(BroadPhasePair{first, second});
            }
        }

        return pairs;
    }
};