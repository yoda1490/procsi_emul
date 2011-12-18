
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
enum mode {REGREG, DIRREG, INDREG, REGIMM, DIRIMM, INDIMM, REGDIR, REGIND};
enum mnemonique {LOAD,STORE,ADD,SUB,JMP,JEQ,CALL,RET,PUSH,POP,HALT};

