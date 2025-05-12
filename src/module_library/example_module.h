#ifndef skelBMLatmos_EXAMPLE_MODULE_H
#define skelBMLatmos_EXAMPLE_MODULE_H

#include <cmath>
#include "../framework/module.h"
#include "../framework/state_map.h"

namespace skelBMLatmos
{
/**
 * @class example_module
 *
 * @brief An example of a very simple direct_module.
 *
 * This module has two inputs (A and B) and two outputs (C and D) whose
 * values are calculated according to the following equations:
 *
 * C = A + B              [Equation (1)]
 *
 * D = A - 0.5 * B        [Equation (2)]
 *
 */
class example_module : public direct_module
{
public:
    example_module(state_map const& input_quantities, state_map* output_quantities)
        : direct_module(),

          // Inputs
          To{get_input(input_quantities, "To")},
          Tr{get_input(input_quantities, "Tr")},
          Ta{get_input(input_quantities, "Ta")},
          Ion{get_input(input_quantities, "Ion")},
          h{get_input(input_quantities, "h")},
          Po{get_input(input_quantities, "Po")},
          BA{get_input(input_quantities, "BA")},
          nu{get_input(input_quantities, "nu")},
          Ps{get_input(input_quantities, "Ps")},

          // Outputs
          Ptilde_op{get_op(output_quantities, "P_tilde")},
          Pb_op{get_op(output_quantities, "Pb")},
          PdR_op{get_op(output_quantities, "PdR")},
          PdA_op{get_op(output_quantities, "PdA")},
          Pas_op{get_op(output_quantities, "Pas")}
    {
    }

    static string_vector get_inputs()
    {
        return {"To", "Tr", "Ta", "Ion", "h", "Po", "BA", "nu", "Ps"};
    }

    static string_vector get_outputs()
    {
        return {"P_tilde", "Pb", "PdR", "PdA", "Pas"};
    }

    static std::string get_name() { return "example_module"; }

private:
    double const& To, &Tr, &Ta, &Ion, &h, &Po, &BA, &nu, &Ps;
    double* Ptilde_op;
    double* Pb_op;
    double* PdR_op;
    double* PdA_op;
    double* Pas_op;

    void do_operation() const
    {
        double sin_h = sin(h);
        double P_tilde = To * Tr * Ta * Ion * sin_h;
        double Pb = To * Tr * Ta * Po * sin_h;
        double PdR = 0.5 * To * Ta * (1.0 - Tr);
        double PdA = BA * To * Tr * Ta * (1.0 - Ta);
        double numerator = Pb + nu * PdR + PdA;
        double denominator = 1.0 - Ps * P_tilde;
        double Pas = (denominator != 0.0) ? Ps * P_tilde * numerator / denominator : 0.0;

        update(Ptilde_op, P_tilde);
        update(Pb_op, Pb);
        update(PdR_op, PdR);
        update(PdA_op, PdA);
        update(Pas_op, Pas);
    }
};

}  // namespace skelBMLatmos

#endif  // skelBMLatmos_EXAMPLE_MODULE_H
