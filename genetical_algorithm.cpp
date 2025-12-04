#include "genetical_algorithm.h"
#include <random>
#include <iostream>

namespace GA
{
    std::random_device rd;
    std::string target_string;

    char genRandomChar() {
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(32, 126);
        return static_cast<char>(dis(gen));
    }

    std::vector<char> genRandomPhrase()
    {
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(32, 126);
        std::vector<char> ret(target_string.length());
        for (int i = 0; i < target_string.length(); i++)
        {
            ret[i] = static_cast<char>(dis(gen));
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(32, 126);
        }
        return ret;
    }

    Carrier::Carrier()
    {
        gens_ = genRandomPhrase();
    }

    bool Carrier::operator<(const Carrier &other) const
    {
        return target_ < other.target();
    }

    Carrier Carrier::newChild(const Carrier &otherParent) const
    {
        std::vector<char> newGens(gens_.size());
        auto &otherGens = otherParent.gens();
        for (auto i = 0; i < gens_.size(); i++)
        {
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, 10);
            if (dis(gen) < 3) {
                newGens[i] = genRandomChar();
                continue;
            }
            
            newGens[i] = gen() % 2 == 0 ? gens_[i] : otherGens[i];

            // if (dis(gen) < 6) {
            //     newGens[i] = newGens[i] == tolower(newGens[i]) ? toupper(newGens[i]) : tolower(newGens[i]);
            //     continue;
            // }
        }
        return {newGens};
    }

    const std::vector<char> &Carrier::gens() const
    {
        return gens_;
    }

    std::optional<double> Carrier::target() const
    {
        return target_;
    }
    void Carrier::setTarget(double target)
    {
        target_ = target;
    }

    std::string Carrier::get_full_str() {
        std::string s(gens_.begin(), gens_.end());
        return s;
    }

    Population::Population(const size_t &size, const unsigned numberRandomCarriers) : size_(size), numberRandomCarriers_(numberRandomCarriers)
    {
        contain_.resize(size);
        for (auto i = 0; i < size; i++)
        {
            contain_[i] = {};
        }
    }

    void Population::evo(const FitnessFunction &fitFunc, const unsigned numberEpoch)
    {
        for (auto i = 0; i < numberEpoch; i++)
        {
            calcFit(fitFunc);
            crossover();
            std::cout << contain_.front().get_full_str() << std::endl;
            std::cout << fitFunc(contain_.front()) << std::endl;
        }
        calcFit(fitFunc);
    }

    void Population::calcFit(const FitnessFunction &fitFunc)
    {
        for (auto &carrier : contain_)
            carrier.setTarget(fitFunc(carrier));

        sort(contain_.begin(), contain_.end());
    }

    void Population::crossover()
    {
        auto &bestParent = contain_.front();
        auto indexLastParent = size_ - numberRandomCarriers_;

        for (auto index = 1; index < indexLastParent + 1; index++)
            contain_[index] = bestParent.newChild(contain_[index]);

        for (auto index = indexLastParent + 1; index < size_; index++)
            contain_[index] = {};
    }

    namespace Tests
    {
        
    }
}
