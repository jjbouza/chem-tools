//
//  ElementDatabase.cpp
//  Chemistry
//
//  Created by Jose Bouza on 2/21/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

#include "ElementDatabase.hpp"

ElementDatabase::ElementDatabase(std::vector<ElementBase> data_in)
{
    ElementDatabase::data = data_in;
}

ElementDatabase::ElementDatabase()
{

    ElementBase H;
    H.init("H",1.01,0);
    ElementBase He;
    He.init("He",4.00,1);
    ElementBase Li;
    Li.init("Li",6.94,2);
    ElementBase Be;
    Be.init("Be",9.01,3);
    ElementBase B;
    B.init("B",10.81,4);
    ElementBase C;
    C.init("C",12.01,5);
    ElementBase N;
    N.init("N",14.01,6);
    ElementBase O;
    O.init("O",16.00,7);
    ElementBase F;
    F.init("F",19.00,8);
    ElementBase Ne;
    Ne.init("Ne",20.18,9);
    ElementBase Na;
    Na.init("Na",22.99,10);
    ElementBase Mg;
    Mg.init("Mg",24.31,11);
    ElementBase Al;
    Al.init("Al",26.98,12);
    ElementBase Si;
    Si.init("Si",28.06,13);
    ElementBase P;
    P.init("P",30.97,14);
    ElementBase S;
    S.init("S",32.07,15);
    ElementBase Cl;
    Cl.init("Cl",35.45,16);
    ElementBase Ar;
    Ar.init("Ar",39.95,17);
    ElementBase K;
    K.init("K",40.00,18);
    ElementBase Ca;
    Ca.init("Ca",40.08,19);
    ElementBase Sc;
    Sc.init("Sc",44.96,20);
    ElementBase Ti;
    Ti.init("Ti",47.87,21);
    ElementBase V;
    V.init("V",50.94,22);
    ElementBase Cr;
    Cr.init("Cr",52.00,23);
    ElementBase Mn;
    Mn.init("Mn",54.94,24);
    ElementBase Fe;
    Fe.init("Fe",55.86,25);
    ElementBase Co;
    Co.init("Co",58.93,26);
    ElementBase Ni;
    Ni.init("Ni",58.69,27);
    ElementBase Cu;
    Cu.init("Cu",63.55,28);
    ElementBase Zn;
    Zn.init("Zn",65.39,29);
    ElementBase Ga;
    Ga.init("Ga",69.72,30);
    ElementBase Ge;
    Ge.init("Ge",72.64,31);
    ElementBase As;
    As.init("As",74.92,32);
    ElementBase Se;
    Se.init("Se",78.96,33);
    ElementBase Br;
    Br.init("Br",79.90,34);
    ElementBase Kr;
    Kr.init("Kr",83.80,35);
    ElementBase Rb;
    Rb.init("Rb",85.47,36);
    ElementBase Sr;
    Sr.init("Sr",87.62,37);
    ElementBase Y;
    Y.init("Y",88.91,38);
    ElementBase Zr;
    Zr.init("Zr",91.22,39);
    ElementBase Nb;
    Nb.init("Nb",92.91,40);
    ElementBase Mo;
    Mo.init("Mo",95.95,41);
    ElementBase Tc;
    Tc.init("Tc",98.00,42);
    ElementBase Ru;
    Ru.init("Ru",101.07,43);
    ElementBase Rh;
    Rh.init("Rh",102.91,44);
    ElementBase Pd;
    Pd.init("Pd",106.42,45);
    ElementBase Ag;
    Ag.init("Ag",107.87,46);
    ElementBase Cd;
    Cd.init("Cd",112.41,47);
    ElementBase In;
    In.init("In",114.82,48);
    ElementBase Sn;
    Sn.init("Sn",118.71,49);
    ElementBase Sb;
    Sb.init("Sb",121.76,50);
    ElementBase Te;
    Te.init("Te",127.60,51);
    ElementBase I;
    I.init("I",126.90,52);
    ElementBase Xe;
    Xe.init("Xe",131.30,53);
    ElementBase Cs;
    Cs.init("Cs",132.91,54);
    ElementBase Ba;
    Ba.init("Ba",137.33,55);
    ElementBase La;
    La.init("La",138.91,56);
    ElementBase Hf;
    Hf.init("Hf",178.49,57);
    ElementBase Ta;
    Ta.init("Ta",180.95,58);
    ElementBase W;
    W.init("W",183.84,59);
    ElementBase Re;
    Re.init("Re",186.21,60);
    ElementBase Os;
    Os.init("Os",190.23,61);
    ElementBase Ir;
    Ir.init("Ir",192.22,62);
    ElementBase Pt;
    Pt.init("Pt",195.08,63);
    ElementBase Au;
    Au.init("Au",196.97,64);
    ElementBase Hg;
    Hg.init("Hg",200.59,65);
    ElementBase Tl;
    Tl.init("Tl",204.38,66);
    ElementBase Pb;
    Pb.init("Pb",207.20,67);
    ElementBase Bi;
    Bi.init("Bi",208.98,68);
    ElementBase Po;
    Po.init("Po",209.00,69);
    ElementBase At;
    At.init("At",210.00,70);
    ElementBase Rn;
    Rn.init("Rn",222.00,71);
    ElementBase Fr;
    Fr.init("Fr",223.00,72);
    ElementBase Ra;
    Ra.init("Ra",226.00,73);
    ElementBase Ac;
    Ac.init("Ac",227.00,74);
    ElementBase Rf;
    Rf.init("Rf",267.00,75);
    ElementBase Db;
    Db.init("Db",268.00,76);
    ElementBase Sg;
    Sg.init("Sg",271.00,77);
    ElementBase Bh;
    Bh.init("Bh",272.00,78);
    ElementBase Hs;
    Hs.init("Hs",270.00,79);
    ElementBase Mt;
    Mt.init("Mt",276.00,80);
    ElementBase Ds;
    Ds.init("Ds",281.00,81);
    ElementBase Rg;
    Rg.init("Rg",280.00,82);
    ElementBase Cn;
    Cn.init("Cn",285.00,83);
    ElementBase Nh;
    Nh.init("Nh",284.00,84);
    ElementBase Fl;
    Fl.init("Fl",289.00,85);
    ElementBase Ce;
    Ce.init("Ce",140.12,86);
    ElementBase Pr;
    Pr.init("Pr",140.91,87);
    ElementBase Nd;
    Nd.init("Nd",144.24,88);
    ElementBase Pm;
    Pm.init("Pm",145.00,89);
    ElementBase Sm;
    Sm.init("Sm",150.36,90);
    ElementBase Eu;
    Eu.init("Eu",151.96,91);
    ElementBase Gd;
    Gd.init("Gd",157.25,92);
    ElementBase Tb;
    Tb.init("Tb",158.93,93);
    ElementBase Dy;
    Dy.init("Dy",162.50,94);
    ElementBase Ho;
    Ho.init("Ho",164.93,95);
    ElementBase Er;
    Er.init("Er",167.26,96); 
    ElementBase Tm;
    Tm.init("Tm",168.93,97); 
    ElementBase Yb;
    Yb.init("Yb",173.05,98); 
    ElementBase Lu;
    Lu.init("Lu",174.97,99); 
    ElementBase Th;
    Th.init("Th",232.04,100); 
    ElementBase Pa;
    Pa.init("Pa",231.04,101); 
    ElementBase U;
    U.init("U",238.03,102); 
    ElementBase Np;
    Np.init("Np",237.00,103); 
    ElementBase Pu;
    Pu.init("Pu",244.00,104); 
    ElementBase Am;
    Am.init("Am",243.00,105); 
    ElementBase Cm;
    Cm.init("Cm",247.00,106); 
    ElementBase Bk;
    Bk.init("Bk",247.00,107); 
    ElementBase Cf;
    Cf.init("Cf",251.00,108); 
    ElementBase Es;
    Es.init("Es",252.00,109); 
    ElementBase Fm;
    Fm.init("Fm",257.00,110); 
    ElementBase Md;
    Md.init("Md",258.00,111); 
    ElementBase No;
    No.init("No",259.00,112); 
    ElementBase Lr;
    Lr.init("Lr",262.00,113); 
 
    
    
    ElementDatabase::data = {H , He , Li , Be , B , C , N , O , F , Ne , Na , Mg , Al , Si , P , S , Cl , K , Ca , Sc , Ti , V , Cr , Mn , Fe , Co , Ni , Cu , Zn
        , Ga , Ge , Se , Br , Kr , Rb , Sr , Y , Zr , Nb , Mo , Tc , Ru , Rh , Pa , Ag , Cd , In , Sn , Sb , Te , I , Xe , Cs , Ba , La , Hf , Ta , W , Re , Os ,
        Ir , Au , Hg , Th , Pb , Bi , Po , At , Rn , Fr , Ra , Ac , Rf , Db , Sg , Bh , Hs , Mt , Ds , Rg , Cn , Nh , Fl , Ce , Pr , Nd , Pm , Sm , Eu , Gd , Tb ,
        Ho , Er , Tm , Yb , Lu , U , Np , Pu , Am , Cm , Bk , Cf , Es , Fm , Md , No , Lr, As, Pd, Pt, Tl, Dy, Ar };
    
}


ElementBase ElementDatabase::find(std::string element_sym)
{
    //Loop through database
    for(ElementBase elem : ElementDatabase::data)
    {
        if(elem.symbol() == element_sym)
            return elem;
    }
    
    //Invalid element name 
    throw std::invalid_argument("Invalid element name: " + element_sym);
}