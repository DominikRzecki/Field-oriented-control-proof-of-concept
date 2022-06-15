//
// Created by dominik on 6/10/22.
//

#ifndef FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_EMF_WAVEFORM_H
#define FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_EMF_WAVEFORM_H

#include <numbers>
#include <array>

namespace dr::foc {

constexpr auto rad = 180/std::numbers::pi_v<float>;

enum class type {
  SINE = 0,
  WAVEFORM = 1
};

  template<size_t EMF_Res>
  class emf_waveform {
  public:
    explicit emf_waveform(foc::type emf_type) {
      emf_type_ = emf_type;
    }

    ~emf_waveform(){ delete EMF_; }

    inline void set_scale(float scale){ scale_ = scale; }

    int operator()(float phase);;

    void set_emf_val(float phase, float value);

  private:
    foc::type emf_type_ {foc::type::SINE};
    std::array<float, EMF_Res> *EMF_ {nullptr};
    float scale_ {1};
  };
  }

#endif // FIELD_ORIENTED_CONTROL_PROOF_OF_CONCEPT_EMF_WAVEFORM_H
