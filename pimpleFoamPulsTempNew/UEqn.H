// Solve the Momentum equation

tmp<fvVectorMatrix> UEqn
(
    fvm::ddt(U)
  + fvm::div(phi, U)
  + turbulence->divDevReff(U)
 ==
    fvOptions(U)
   +dpdx*cos(Freq*runTime.time().value())
);

UEqn().relax();

fvOptions.constrain(UEqn());

volScalarField rAU(1.0/UEqn().A());

if (pimple.momentumPredictor())
{
    solve(UEqn() == -fvc::grad(p));
    //solve(UEqn() == -fvc::grad(p)-dpdx);
    fvOptions.correct(U);
}
