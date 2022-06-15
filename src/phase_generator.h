//
// Created by dominik on 6/10/22.
//

#ifndef FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_PHASE_GENERATOR_H
#define FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_PHASE_GENERATOR_H

#include <Arduino.h>

#include "emf_waveform.h"

namespace dr::foc {

  template <std::size_t EMF_Res> class phase_generator {
  public:
    phase_generator() = default;
    explicit phase_generator(int8_t pin, float phase_rad, dr::foc::emf_waveform<EMF_Res>& active_waveform) :active_waveform_ {active_waveform}, phase_rad_{phase_rad}, pin_{pin} {}

    inline void set_EMF_waveform(dr::foc::emf_waveform<EMF_Res>& active_waveform) { active_waveform_ = active_waveform; }

    inline void update(float phase) {
        if(active_waveform_) {
          float R = 50;
          auto current = (analogRead(A0)/1024.0f)*12;//<- peak current
          auto target_current = active_waveform_(phase);
          auto backEMF = out_voltage - (current * R);
          out_voltage = target_current * R + backEMF;
          analogWrite(pin_, (out_voltage/20)*255);
        }
    };
  private:

    dr::foc::emf_waveform<EMF_Res>* active_waveform_ {nullptr};
    float phase_rad_ {0};
    int8_t pin_ {11};
    float out_voltage;
  };

  ISR();
} // namespace dr::foc

#endif // FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_PHASE_GENERATOR_H