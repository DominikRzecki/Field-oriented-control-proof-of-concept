//
// Created by dominik on 6/10/22.
//

#include <cmath>
#include "emf_waveform.h"

template <size_t EMF_Res> int dr::foc::emf_waveform<EMF_Res>::operator()(float phase) {
  switch(emf_type_) {
  case foc::type::SINE:
    return std::sin(phase);
    break;
  case foc::type::WAVEFORM:
    if (EMF_) {
      return EMF_->at(static_cast<int>(phase / (2 * std::numbers::pi_v<float>)*EMF_Res)) * scale_;
    } else {
      return 0;
    }
    break;
  }
}
template <size_t EMF_Res>
void dr::foc::emf_waveform<EMF_Res>::set_emf_val(float phase, float value) {
  if(!EMF_) {
    EMF_ = new std::array<float, EMF_Res>;
  }
  EMF_->at(static_cast<int>(phase / (2 * std::numbers::pi_v<float>)*EMF_Res)) = value;
}