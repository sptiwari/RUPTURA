#include "component.h"

#include <iostream>
#include <string>

#include "isotherm.h"

Component::Component(size_t _id, std::string _name, std::vector<Isotherm> _isotherms, double _Yi0, double _Kl,
                     double _D, double _Kn, bool _isCarrierGas)
    : id(_id), name(_name), Yi0(_Yi0), Kl(_Kl), D(_D), Kn(_Kn), isCarrierGas(_isCarrierGas)
{
  // Note: useConcentrationDependentKinetics is initialized to false by default in the header
  // It will be set to true by the InputReader if the Kn parameter is provided.
  isotherm.numberOfSites = _isotherms.size();
  for (Isotherm it : _isotherms)
  {
    isotherm.add(it);
  }
}

void Component::print() const { std::cout << repr(); }

std::string Component::repr() const
{
  std::string s;
  s += "Component id: " + std::to_string(id) + " [" + name + "]:\n";
  if (isCarrierGas)
  {
    s += "    carrier-gas\n";
    s += isotherm.repr();
  }
  s += "    mol-fraction in the gas:   " + std::to_string(Yi0) + " [-]\n";
  if (!isCarrierGas)
  {
    s += "    mas-transfer coefficient: " + std::to_string(Kl) + " [1/s]\n";
    s += "    diffusion coefficient:     " + std::to_string(D) + " [m^2/s]\n";
    s += isotherm.repr();
  }
  return s;
}
