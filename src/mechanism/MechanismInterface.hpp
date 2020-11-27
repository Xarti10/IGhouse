#ifndef IGHOUSE_MECHANISMINTERFACE_HPP
#define IGHOUSE_MECHANISMINTERFACE_HPP

namespace IGHouse
{
namespace Mechanism
{

class MechanismInterface
{
public:
    MechanismInterface() = default;
    virtual ~MechanismInterface() = default;

    virtual void runObservation() = 0;
    virtual void turnOff() = 0;
    virtual void turnOn() = 0;

private:
    virtual void init() = 0;
};

}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_MECHANISMINTERFACE_HPP
