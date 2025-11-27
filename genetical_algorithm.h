#pragma once

#include <ranges>
#include <functional>
#include <optional>
#include <string>

namespace GA
{
    class Carrier
    {
    public:
        Carrier();
        Carrier(const std::vector<char> &gens) : gens_(gens) {}

        bool operator<(const Carrier &other) const;

        Carrier newChild(const Carrier &otherParent) const;
        const std::vector<char> &gens() const;
        std::string get_full_str();

        std::optional<double> target() const;
        void setTarget(double);

    private:
        std::vector<char> gens_;
        std::optional<double> target_;
    };

    class Population
    {
    public:
        using FitnessFunction = std::function<double(const Carrier &)>;

        Population(const size_t &size, const unsigned numberRandomCarriers);

        void evo(const FitnessFunction &fitFunc, const unsigned numberEpoch);

    private:
        void calcFit(const FitnessFunction &fitFunction);
        void crossover();

    private:
        size_t size_;
        unsigned numberRandomCarriers_;
        std::vector<Carrier> contain_;
    };
}
