typedef union
{
    short brut;
    struct
    {
        unsigned codeop : 6;
        unsigned mode : 4;
        unsigned source : 3;
        unsigned dest : 3;
    }codage;
}mot;

// Modes d'adressage des instructions
enum mode {REGREG, REGIMM, REGDIR, REGIND, DIRIMM, DIRREG, INDIMM, INDREG};
enum mnemonique {LOAD,STORE,JMP,ADD,SUB};

const int TAILLE_MEM = 5;

// Tableaux de tout les mot


