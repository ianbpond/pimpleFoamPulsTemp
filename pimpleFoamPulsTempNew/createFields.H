Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

//Info<< "Reading field alphat\n" << endl;
//    volScalarField alphat
//    (
//        IOobject
//        (
//            "alphat",
//            runTime.timeName(),
//            mesh,
//           IOobject::MUST_READ,
//            IOobject::AUTO_WRITE
//        ),
//        mesh
//    );

    // Reference temperature [K]
    dimensionedScalar TRef
    (
	transportProperties.lookup("TRef")
    );

    // Laminar Prandtl number
    dimensionedScalar Pr
    (
	transportProperties.lookup("Pr")
    );

    // Turbulent Prandtl number
    dimensionedScalar Prt
    (
	transportProperties.lookup("Prt")
    );


//This is added to lookup the value of dpdx in transportProperties
dimensionedVector dpdx
(

    transportProperties.lookup("dpdx")

);
//Look up Period of flow
dimensionedScalar Freq
(

    transportProperties.lookup("Freq")
    

);


    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
 
#include "createPhi.H"


label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, mesh.solutionDict().subDict("PIMPLE"), pRefCell, pRefValue);


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);
