// IRIS GEANT4 DETECTOR MASS MODEL SIMULATION
//
// FAST BOARD RUNS: 2110/2111
//

// ORDER, PLACEMENTS, & SIZES OF OBJECTS:
// 1. 'WORLD':: Position = (0,0,0); Size: (x,y,z) = (150cm, 150cm, 200)
// 2. 'ENVELOPE'::  Position = (0,0,0); Size: (x,y,z) = (120cm, 120cm, 150cm)
// 3. 'WALL OF WATER 1':: Position: (0, 0, -11.5); Size: (x, y, z) = (30cm, 30cm, 5cm)
// 4. 'LEAD SHEETS':: N = 3 Sheets; Position: (0, 0, -8.5); Size: (x, y, z) = (30cm, 30cm, 1cm)
// 5. 'WALL OF WATER 2':: Position = (0, 0, -7.0); Size: (x, y, z) = (30cm, 30cm, 2cm)
// 6. 'ACRYLIC BLOCK':: Position = (0,-14.0,0); size = (4cm, 4cm, 12cm)
// 7. 'CUBE OF WATER':: Position = (INSIDE ACRYLIC BLOCK) = (0, -14.0, -4.0);  size = (1cm, 1cm, 1 cm)
// 8. 'ALUMINUM IRIS ENCLOSURE':: Position = (0, 0, 0); Size: (x,y,z) = (12.1cm, 12.1cm, 9.5cm)
// 9. 'PLASTIC SCINTILLATOR COVER (PSC)':: Position = (Inside enclosure) = (0, 0, 2.0); Size: (x,y,z) = (.9cm, .9cm, 5cm)
// 10.'LYSO CRYSTAL':: Position = (INSIDE 'PSC') = (0, 0, 1.0); Size: (x,y,z) = (0.4cm, 0.4cm, 2.2cm);
// 11.'SILICON WAFER':: Position = (UNDER LYSO CRYSTAL) = (0, 0, 1.5); Size: (x, y, z) = (0.05, 0.05cm, 0.0001cm or 1 micron)
// 12. 'STEEL TABLE':: Position = (UNDERNEATH ALL OF THE ABOVE) = (0, 0, +8.5); Size = (x,y,z) = (50cm, 50cm, 4cm)


#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
//#include "G4PVDivision.hh"
#include "G4VSolid.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisManager.hh"
#include "SteppingAction.hh"

#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
 
 
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// 1. 'WORLD' Position:: (0,0,0);  Size: (x,y,z) = (90cm, 90cm, 120)
//
   // Envelope parameters
  //
  G4double env_sizeXY = 31*cm, env_sizeZ = 100*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World",                           // its name
    0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
    world_mat,                                       // its material
    "World");                                        // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                           // at (0,0,0)
    logicWorld,                                // its logical volume
    "World",                                   // its name
    nullptr,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    checkOverlaps);                            // overlaps checking
   
 
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......    
//
// 2. 'ENVELOPE' Position:: (0,0,0); Size: (x,y,z) = (75cm, 75cm, 100cm)
//
//
  auto solidEnv = new G4Box("Envelope",                    // its name
    0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
    env_mat,                                     // its material
    "Envelope");                                 // its name

  new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),          // at (0,0,0)
    logicEnv,                 // its logical volume
    "Envelope",               // its name
    logicWorld,               // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checking

//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 3. 'WALL OF WATER 1':: Position: (0, 0, -11.5); Size: (x, y, z) = (30cm, 30cm, 5cm)
//
/*
 //SET UP C
  G4Material *Shape3_mat
    = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos3 = G4ThreeVector(0, 0, -12 * cm);
 
 
  //SET UP F
  G4Material *Shape3_mat
    = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos3 = G4ThreeVector(0, 0, -13.5 * cm);
 
  G4double WATER_WALL_UNO_hx = 30/2.0 * cm;
  G4double WATER_WALL_UNO_hy = 30/2.0 * cm;
  G4double WATER_WALL__UNO_hz = 5.0/2.0 * cm;  
 
  auto solidShape3 = new G4Box("WATER_WALL_UNO",  WATER_WALL_UNO_hx,    WATER_WALL_UNO_hy,  WATER_WALL__UNO_hz);  

  auto logicShape3 = new G4LogicalVolume(solidShape3,  // its solid
    Shape3_mat,                                        // its material
    "WATER_WALL_UNO");                                 // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos3,                     // at position
    logicShape3,              // its logical volume
    "WATER_WALL_UNO",         // its name
    logicEnv,                 // its mother  volume - INSIDE ENVELOPE
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
   
   
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 4. 'LEAD SHEETS':: N = 3 Sheets = ~ 1cm thick; Position: (0, 0, -8.5); Size: (x, y, z) = (30cm, 30cm, 1cm)
//
 /*
 //SET UP C
  G4Material *Shape4_mat
    = nist->FindOrBuildMaterial("G4_Pb"); //Lead
  G4ThreeVector pos4 = G4ThreeVector(0, 0, -9.0 * cm); //Between the walls of water
 
  G4double Lead_Sheet_hx = 30/2.0 * cm;
  G4double Lead_Sheet_hy = 30/2.0 * cm;
  G4double Lead_Sheet_hz = 1.0/2.0 * cm;
 
 
 //SET UP F
  G4Material *Shape4_mat
    = nist->FindOrBuildMaterial("G4_Pb"); //Lead
  G4ThreeVector pos4 = G4ThreeVector(0, 0, -9.5 * cm); //Between the walls of water
 
  G4double Lead_Sheet_hx = 30/2.0 * cm;
  G4double Lead_Sheet_hy = 30/2.0 * cm;
  G4double Lead_Sheet_hz = 3.0/2.0 * cm;

  auto solidShape4 = new G4Box("LEAD_SHEETS", Lead_Sheet_hx, Lead_Sheet_hy, Lead_Sheet_hz);  

  auto logicShape4 = new G4LogicalVolume(solidShape4,  // its solid
    Shape4_mat,                                        // its material
    "LEAD_SHEETS");                                    // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos4,                     // at position
    logicShape4,              // its logical volume
    "LEAD_SHEETS",            // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
 
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 5. 'WALL OF WATER 2':: Position = (0, 0, -7.0); Size: (x, y, z) = (30cm, 30cm, 2cm)
//

  G4Material *Shape5_mat
    = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos5 = G4ThreeVector(0, 0, -7.5 * cm);
 
  G4double WATER_WALL_DOS_hx = 30/2.0 * cm;
  G4double WATER_WALL_DOS_hy = 30/2.0 * cm;
  G4double WATER_WALL_DOS_hz = 2.0/2.0 * cm;
 

  auto solidShape5 = new G4Box("WATER_WALL_DOS",  WATER_WALL_DOS_hx,  WATER_WALL_DOS_hy,  WATER_WALL_DOS_hz);  

  auto logicShape5 = new G4LogicalVolume(solidShape5,  // its solid
    Shape5_mat,                                        // its material
    "WATER_WALL_DOS");                                 // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos5,                     // at position
    logicShape5,              // its logical volume
    "WATER_WALL_DOS",         // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
*/  
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// 6. 'ACRYLIC BLOCK':: Position = (0,-14.0,0); size = (4cm, 4cm, 12cm)
//
 
  // Material definitions of Acrylic components
  G4double z, a, density;
  G4String name, symbol;
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  G4double temperature, pressure;
 
  G4Element* elH = new G4Element (name="Hydrogen",symbol="H",z=1.,a=1.00794*g/mole);
  G4Element* elC = new G4Element (name="Carbon",symbol="C",z=6.,a=12.011*g/mole);
  G4Element* elO = new G4Element (name="Oxygen",symbol="O",z=8.,a=16.00*g/mole);

  // Acrylic
  G4Material* Acrylic = new G4Material (name="Acrylic", density= 1.18*g/cm3, ncomponents=3);
  Acrylic->AddElement(elC,natoms=5);
  Acrylic->AddElement(elH,natoms=8);
  Acrylic->AddElement(elO,natoms=2);
 
  G4ThreeVector pos6 = G4ThreeVector(0, -9 * cm, 4*cm);
 
  //DIMENSIONS OF ACRYLIC BLOCK: size = (4cm, 4cm, 12cm)
  G4double ACRYLIC_hx = 4/2.0 * cm;
  G4double ACRYLIC_hy = 4/2.0 * cm;
  G4double ACRYLIC_hz = 12/2.0 * cm;
 
  auto solidShape6 = new G4Box("ACRYLIC_BLOCK", ACRYLIC_hx, ACRYLIC_hy, ACRYLIC_hz);

  auto logicShape6 = new G4LogicalVolume(solidShape6,  // its solid
    Acrylic,                                           // its material
    "ACRYLIC_BLOCK");                                  // its name

  new G4PVPlacement(nullptr,   // no rotation
    pos6,                      // at position
    logicShape6,               // its logical volume
    "ACRYLIC_BLOCK",           // its name
    logicEnv,                  // its mother  volume - inside the plastic cover!
    false,                     // no boolean operation
    0,                         // copy number
    checkOverlaps);            // overlaps checkingG4Material
   
 
  G4Material *Si
    = nist->FindOrBuildMaterial("G4_Si");
  G4Material *Pb
    = nist->FindOrBuildMaterial("G4_Pb");
  G4Material *Nai
    = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4Material *BGO
    = nist->FindOrBuildMaterial("G4_BGO");
   
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// 7. 'CUBE OF WATER':: Position = (INSIDE ACRYLIC BLOCK) = (0, -14.0, -4.0);  size = (1cm, 1cm, 1 cm)
//

  G4Material *Shape7_mat
    = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos7 = G4ThreeVector(0, 0, -4 * cm);
 
  G4double WATER_CUBE_hx = 1.0/2.0 * cm;
  G4double WATER_CUBE_hy = 1.0/2.0 * cm;
  G4double WATER_CUBE_hz = 1.0/2.0 * cm;
 
//  G4double WATER_CUBE_hx = .4/2.0 * cm;
//  G4double WATER_CUBE_hy = .4/2.0 * cm;
//  G4double WATER_CUBE_hz = 2.2/2.0 * cm;
 
  auto solidShape7 = new G4Box("WATER_CUBE",  WATER_CUBE_hx,  WATER_CUBE_hy,  WATER_CUBE_hz);  

  auto logicShape7 = new G4LogicalVolume(solidShape7,  // its solid
    Shape7_mat,                                        // its material
    "WATER_CUBE");                                     // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos7,                     // at position
    logicShape7,              // its logical volume
    "WATER_CUBE",             // its name
    logicShape6,                 // its mother  volume **eventually this will be something like ' logicAcrylic'
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
 
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 8. 'ALUMINUM IRIS ENCLOSURE':: Position = (0, 0, 0); Size: (x,y,z) = (12.1cm, 12.1cm, 9.5cm)
//
//
 
  G4Material* Enclosure_mat = nist->FindOrBuildMaterial("G4_Al"); //Aluminum
  G4ThreeVector pos8 = G4ThreeVector(0, 0, 0); //centered in world and envelope
 
  //
  // NOTE: See the engineering schematics listed on the polycase website for AL-75P Diecast Aluminum Enclosure
  //
  //EXPLICIT CALCULATIONS: Dimensions of Outer Box:
  //
  // outer_box_px = 12.1 cm
  // outer_box_py = 12.1 cm
  // outer_box_pz = 9.5 cm
 
  G4double outer_box_hx = 12.1/2.0 * cm;
  G4double outer_box_hy = 12.1/2.0 * cm;
  G4double outer_box_hz = 9.5/2.0 * cm;  
 
  //EXPLICIT CALCULATIONS: Dimensions of inner box
  //
  //px_in = [outer_box_px] - 2[Wall thickness] = 12.1cm - (2*0.23876cm) = 11.62248 cm
  //Wrong: py_in = [outer_box_py] - [Top thickness + Base thickness] = 12.1cm - (0.19812cm + 0.56134cm) = 11.34054 cm
  //py_in = [outer_box_py] - [Top thickness + Base thickness] = 12.1cm - 2(0.19812cm) = 11.70376 cm
  //pz_in = [outer+box_pz] - 2[Wall thickness] = 9.5cm - 2(0.23876cm) = 9.02248 cm
 
  G4double inner_box_hx = 11.6/2.0 * cm;
  G4double inner_box_hy = 11.7/2.0 * cm;
  G4double inner_box_hz = 9.0/2.0 * cm;
 
 
  G4Box* Outer_Box
    = new G4Box("Outer_Box",
                outer_box_hx,
                outer_box_hy,
                outer_box_hz);

  G4Box* Inner_Box
    = new G4Box("Inner_box",
                inner_box_hx,
                inner_box_hy,
                inner_box_hz);
               
               
  //Relevant thicknesses:          
  //NOTE: we are flipping it so that the usual bottom is the new lid/ new base thickness: 0.221’’ = 0.56134 cm              
  //Top thickness: 0.078’’ = 0.19812 cm
  //Wall thickness (sides): 0.094’’ =  0.23876 cm (x4 sides)
               
  G4SubtractionSolid *solidBox =
new G4SubtractionSolid("Enclosure", Outer_Box, Inner_Box);  

  G4LogicalVolume* logicBox =
      new G4LogicalVolume(solidBox,         //its solid
                          Enclosure_mat,    //its material
                          "Enclosure");     //its name
                         
 
  new G4PVPlacement(nullptr,  // no rotation
    pos8,                     // at position
    logicBox,                 // its logical volume
    "Enclosure",              // its name
    logicEnv,                 // its mother  volume - inside ENVELOPE
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
   
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 9. 'PLASTIC SCINTILLATOR COVER (PSC)':: Position = (Inside enclosure) = (0, 0, 2.0); Size: (x,y,z) = (.9cm, .9cm, 5cm)
//
 
  G4Material *Plcov_mat
    = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4ThreeVector pos9 = G4ThreeVector(0, 0, 0 * cm);
 
  G4double Plcov_outer_hx = 2.1/2.0 * cm;
  G4double Plcov_outer_hy = 2.1/2.0 * cm;
  G4double Plcov_outer_hz = 4.5/2.0 * cm;
 
  G4double Plcov_inner_hx = .635/2.0 * cm;
  G4double Plcov_inner_hy = .635/2.0 * cm;
  G4double Plcov_inner_hz = 4.4/2.0 * cm;
 
 

  G4Box* Outer_Plcov
    = new G4Box("Outer_Plcov",
                Plcov_outer_hx,
                Plcov_outer_hy,
                Plcov_outer_hz);

  G4Box* Inner_Plcov
    = new G4Box("Inner_Plcov",
                Plcov_inner_hx,
                Plcov_inner_hy,
                Plcov_inner_hz);
               
  G4SubtractionSolid *solidCov =
new G4SubtractionSolid("CRYSTAL_COVER", Outer_Plcov, Inner_Plcov);

  G4LogicalVolume* logicCov =
      new G4LogicalVolume(solidCov,         //its solid
                          Plcov_mat,        //its material
                          "CRYSTAL_COVER"); //its name
                         
 
  new G4PVPlacement(nullptr,  // no rotation
    pos9,                     // at position
    logicCov,                 // its logical volume
    "CRYSTAL_COVER",          // its name
    logicEnv,                 // its mother  volume - inside the Al enclosure!
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
   
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 10.'LYSO CRYSTAL':: Position = (INSIDE 'PSC') = (0, 0, 1.0); Size: (x,y,z) = (0.4cm, 0.4cm, 2.2cm);  
//
 
  // Material definitions of Lutetium–yttrium oxyorthosilicate (LYSO) components
  /*G4double z, a, density;
  G4String name, symbol;
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  G4double temperature, pressure;
  */

  a = 174.97*g/mole;
  G4Element* elLu = new G4Element(name="Lutetium", symbol="Lu", z=71., a);

  a = 88.91*g/mole;
  G4Element* elY  = new G4Element(name="Yttrium",symbol="Y",z=39.,a);

  a = 28.09*g/mole;
  G4Element* elSi  = new G4Element("Silicon","Si",z=14.,a);

  //a  = 16.00*g/mole;
  //G4Element* elO   =  new G4Element("Oxygen","O",z=8.,a);

  // Lu2(1-x), if x = 0.075, then Lu(1.85)
  // Y2(.075), if x = 0.075, then Y(0.15)
  // Si = 1
  // O5 = 5
  // The total molar mass is: (1.85*174.97) + (0.15*88.91) + (28.09) + (5*16) = 445.121 g/mol
  // Then the fracmass of Lu IS: (1.85 * 174.97)/(445.121) = 0.7272 => 73%
  // SIMILARLY FOR % Y: (0.15 * 88.91)/(445.121) = 0.0299 => 3%
  // SIMILARLY FOR % Si: (28.09)/(445.121) = 0.063 => 6%
  // SIMILARLY FOR % 0: (80)/(445.121)= 0.1797 => 18%
  // CHECK: 73 + 3 + 6 + 18 = 100


  density = 7.16*g/cm3 ;
  G4Material* lyso = new G4Material(name="LYSO",density,ncomponents=4);
  lyso->AddElement(elLu, fractionmass=.73);
  lyso->AddElement(elY, fractionmass=.03);
  lyso->AddElement(elSi, fractionmass=.06);
  lyso->AddElement(elO, fractionmass=.18);
 
  //G4Material *lyso_mat = lyso;
  //G4Material* shape10_mat = nist->FindOrBuildMaterial("LYSO");
  G4ThreeVector pos10 = G4ThreeVector(0, 0, .998 * cm);
 
  //DIMENSIONS OF LYSO CRYSTAL: 4x4x22mm = 0.40 cm x 0.40 cm x 2.2 cm
  G4double lyso_hx = .4/2.0 * cm;
  G4double lyso_hy = .4/2.0 * cm;
  G4double lyso_hz = 2.2/2.0 * cm;
 

  auto solidShape10 = new G4Box("CRYSTAL", lyso_hx, lyso_hy, lyso_hz);

  auto logicShape10 = new G4LogicalVolume(solidShape10, // its solid
    lyso,                                        // its material
    "CRYSTAL");                                         // its name

  new G4PVPlacement(nullptr,   // no rotation
    pos10,                     // at position
    logicShape10,              // its logical volume
    "CRYSTAL",                 // its name
    logicEnv,                  // its mother  volume - inside the plastic cover!
    false,                     // no boolean operation
    0,                         // copy number
    checkOverlaps);            // overlaps checkingG4Material
   
    //fScoringVolume = logicShape10;
 
   
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//  
// 11.'SILICON WAFER':: Position = (UNDER LYSO CRYSTAL) = (0, 0, 1.5); Size: (x, y, z) = (0.05, 0.05cm, 0.0001cm or 1 micron)
//

  G4Material *Shape11_mat
    = nist->FindOrBuildMaterial("G4_Si");         //Silicon
  //G4ThreeVector pos11 = G4ThreeVector(0., 0, 2.1* cm); //centered below the scint crystal and inside the cover
 
  G4ThreeVector pos11 = G4ThreeVector(0., -3.0* cm, 2.1* cm); //centered below the scint crystal and inside the cover
 
  //G4double SILICON_WAFER_hx = 0.285/2.0 * cm;
  //G4double SILICON_WAFER_hy = 0.285/2.0 * cm;
 
  G4double SILICON_WAFER_hx = 2.0/2.0 * cm;
  G4double SILICON_WAFER_hy = 2.0/2.0 * cm;
  G4double SILICON_WAFER_hz = 0.01/2.0 * cm;
 
  auto solidShape11 = new G4Box("SILICON_WAFER",  SILICON_WAFER_hx,  SILICON_WAFER_hy,  SILICON_WAFER_hz);  

  auto logicShape11 = new G4LogicalVolume(solidShape11, // its solid
    Shape11_mat,                                        // its material
    "SILICON_WAFER");                                   // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos11,                    // at position
    logicShape11,              // its logical volume
    "SILICON_WAFER",          // its name
    logicEnv,                 // its mother  volume - inside the Al enclosure, but external to scint cover and crystal
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
 
 
   
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// Shape 12. 'STEEL TABLE':: Position = (UNDERNEATH ALL OF THE OBJECTS ABOVE) = (0, 0, +8.5); Size = (x,y,z) = (50cm, 50cm, 4cm)
//
 
  //a = 12.02*g/mole;
  //G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);

  a = 55.85*g/mole;
  G4Element* elFe  = new G4Element(name="Iron",symbol="Fe",z=26.,a);

  a  =  54.94*g/mole;
  G4Element* elMn   =  new G4Element("Manganese","Mn",z=25.,a);

  //a = 28.09*g/mole;
  //G4Element* elSi  = new G4Element("Silicon","Si",z=14.,a);
 
  density = 7.84*g/cm3 ;
  G4Material* steel = new G4Material(name="Steel",density,ncomponents=4);
  steel->AddElement(elMn, 0.0165);
  steel->AddElement(elSi, 0.01);
  steel->AddElement(elC, 0.005);
  steel->AddElement(elFe, 0.9685);
 
  G4ThreeVector pos12 = G4ThreeVector(0, 0, 20.0 * cm); //Below all of the objects listed above
 
  G4double STEEL_TABLE_hx = 30/2.0 * cm;
  G4double STEEL_TABLE_hy = 30/2.0 * cm;
  G4double STEEL_TABLE_hz = 4.0/2.0 * cm;
 
  auto solidShape12 = new G4Box("STEEL_TABLE", STEEL_TABLE_hx, STEEL_TABLE_hy, STEEL_TABLE_hz);

  auto logicShape12 = new G4LogicalVolume(solidShape12,  // its solid
    steel,                                               // its material
    "STEEL_TABLE");                                      // its name

  new G4PVPlacement(nullptr,  // no rotation
    pos12,                    // at position
    logicShape12,             // its logical volume
    "STEEL_TABLE",            // its name
    logicEnv,                 // its mother  volume
    false,                    // no boolean operation
    0,                        // copy number
    checkOverlaps);           // overlaps checkingG4Material
   
 
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// UNCOMMENT BELOW TO CHOOSE WHICH OBJECT YOU WANT THE ENERGY DOSAGE FROM - DO SO ONE AT A TIME FOR NOW...
//

  //fScoringVolume = logicWorld;   // 1. 'WORLD' = AIR
  //fScoringVolume = logicEnv;     // 2. 'ENVELOPE' = AIR
  //fScoringVolume = logicShape3;  // 3. 'WALL OF WATER 1'
  //fScoringVolume = logicShape4;  // 4. '3 LEAD SHEETS'
  //fScoringVolume = logicShape5;  // 5. 'WALL OF WATER 2'
  //fScoringVolume = logicShape6;  // 6. 'ACRYLIC BLOCK'
  //fScoringVolume = logicShape7;  // 7. 'CUBE OF WATER'
  //fScoringVolume = logicBox;     // 8. 'ALUMINUM IRIS ENCLOSURE'
  //fScoringVolume = logicCov;     // 9. 'PLASTIC SCINTILLATOR COVER'
  //fScoringVolume = logicShape10;   // 10.'LYSO CRYSTAL'
  fScoringVolume = logicShape11; // 11.'SILICON WAFER'
  //fScoringVolume = logicShape12; // 12. 'STEEL TABLE'
 
 
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
// VISUAL ATTRIBUTES: e.g. INVISIBLE, WIREFRAME, COLOR, ETC...
//
 
  logicWorld->  SetVisAttributes(G4VisAttributes::GetInvisible());            // 1. 'WORLD' = invisible  
  //logicEnv->  SetVisAttributes(G4VisAttributes::GetInvisible());            // 2. 'ENVELOPE' = invisible
  logicEnv-> SetVisAttributes(new G4VisAttributes(G4Colour(1.,0.,1.)));       // 2. 'envelope' = purple (magenta)
  //logicShape3-> SetVisAttributes(new G4VisAttributes(G4Colour(1.,0.,1.)));    // 3. 'WALL OF WATER 1' = magenta
  //logicShape4-> SetVisAttributes(new G4VisAttributes(G4Colour(0.,1.,0.)));    // 4. '3 LEAD SHEETS' = green
  //logicShape5-> SetVisAttributes(new G4VisAttributes(G4Colour(1.,0.,1.)));    // 5. 'WALL OF WATER 2' = magenta
  logicShape6-> SetVisAttributes(new G4VisAttributes(G4Colour(1.,1.,0.)));    // 6. 'ACRYLIC BLOCK' = yellow
  logicShape7-> SetVisAttributes(new G4VisAttributes(G4Colour(0.,0.,1.)));    // 7. 'CUBE OF WATER' = blue
  logicBox-> SetVisAttributes(new G4VisAttributes(G4Colour(0.,0.,1.)));       // 8. 'ALUMINUM IRIS ENCLOSURE' = blue
  logicCov-> SetVisAttributes(new G4VisAttributes(G4Colour(1.,0.,0.)));       // 9. 'PLASTIC SCINTILLATOR COVER' = red
  logicShape10-> SetVisAttributes(new G4VisAttributes(G4Colour(0.,1.,0.)));   // 10.'LYSO CRYSTAL' = green
  logicShape11->  SetVisAttributes(new G4VisAttributes(G4Colour(1.,1.,0.)));  // 11.'SILICON WAFER' = yellow                    
  logicShape12-> SetVisAttributes(new G4VisAttributes(G4Colour(0.,0.,1.)));   // 12. 'STEEL TABLE' = blue


//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......
//
//ALWAYS RETURN TO THE PHYSICAL WORLD
//

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo..........oooOO0OOooo......

}
