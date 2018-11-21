//
// Created by JJJJJJJiyun on 2018/11/20.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "Syntax.h"

const int INT[] = {PLUS, MINUS, UNSIGNEDINT, ZERO};
const int INT_SIZE = 4;
const int NUM[] = {LESSEQU, GREATEQU, EQUAL, NEQUAL, LESS, GREAT, PLUS, MINUS, MULTI, DIVIDE, COMMA, SEMICOLON,
                   RBRACK, RPARENT};
const int NUM_SIZE = 14;
const int END[] = {SEMICOLON, COMMA};
const int END_SIZE = 2;
const int VARDEF[] = {LBRACK, COMMA, SEMICOLON};
const int VARDEF_SIZE = 3;
const int DEF[] = {INTSYM, CHARSYM};
const int DEF_SIZE = 2;
const int STATEMENT[] = {IFSYM, DOSYM, WHILESYM, FORSYM, PRINTFSYM, SCANFSYM, RETURNSYM, LBRACE, SEMICOLON, ID};
const int STATEMENT_SIZE = 10;
const int FACTOR[] = {PLUS, MINUS, MULTI, DIVIDE, SEMICOLON, COMMA, RPARENT, RBRACK};
const int FACTOR_SIZE = 8;
const int CONST[] = {CHAR, PLUS, MINUS, UNSIGNEDINT, ZERO};
const int CONST_SIZE = 5;
const int RELATION[] = {LESSEQU, GREATEQU, EQUAL, NEQUAL, LESS, GREAT};
const int RELATION_SIZE = 6;


void Compiler::constructInt(int *value) {
    bool flag = false;
    int result = 0;
    if (this->sym == 0) {
        this->errorHandle(UNSIGNEDINTERROR);
        this->skip(NUM, NUM_SIZE);
    } else {
        if (this->sym == PLUS || this->sym == MINUS) {
            flag = this->sym == MINUS;
            this->getSym();
            if (this->sym == UNSIGNEDINT) {
                result = std::atoi(this->token.c_str());
                this->getSym();
            } else {
                this->errorHandle(UNSIGNEDINTERROR);
                this->skip(NUM, NUM_SIZE);
            }
        } else {
            result = std::atoi(this->token.c_str());
            this->getSym();
        }
    }
    *value = flag ? -result : result;
}

void Compiler::constDef() {
    std::cout << "const def" << std::endl;
    int symbolType = CONSTSYM;
    if (this->sym == INTSYM) {
        int returnType = INTSYM;
        do {
            std::cout << "num const" << std::endl;
            int value = 0;
            std::string *name = 0;
            this->getSym();
            if (this->sym == ID) {
                name = new std::string(this->token);
                this->getSym();
                if (this->sym == ASSIGN)
                    this->getSym();
                else {
                    this->errorHandle(ASSIGNERROR);
                    this->skip(INT, INT_SIZE);
                }
                if (this->isInTarget(INT, INT_SIZE)) {
                    this->constructInt(&value);
                    symbol *sym = 0;
                    if (!this->find(name, &sym, true))
                        this->push(name, returnType, symbolType, value, this->line);
                    else this->errorHandle(DUPLICATEERROR);
                } else {
                    this->errorHandle(INTERROR);
                    this->skip(END, END_SIZE);
                }
            } else {
                this->errorHandle(IDERROR);
                this->skip(END, END_SIZE);
            }
        } while (this->sym == COMMA);
    } else if (this->sym == CHARSYM) {
        int returnType = CHARSYM;
        do {
            std::cout << "char const" << std::endl;
            int value = 0;
            std::string *name = 0;
            this->getSym();
            if (this->sym == ID) {
                name = new std::string(this->token);
                this->getSym();
                if (this->sym == ASSIGN) this->getSym();
                else {
                    this->errorHandle(SINGLECHARERROR);
                    this->skip(CHAR);
                }
                if (this->sym == CHAR) {
                    value = this->token[0];
                    symbol *sym = 0;
                    if (!this->find(name, &sym, true)) this->push(name, returnType, symbolType, value, this->line);
                    else this->errorHandle(DUPLICATEERROR);
                    this->getSym();
                } else {
                    this->errorHandle(SINGLECHARERROR);
                    this->skip(END, END_SIZE);
                }
            } else {
                this->errorHandle(IDERROR);
                this->skip(END, END_SIZE);
            }
        } while (this->sym == COMMA);
    } else {
        this->errorHandle(INTORCHARERROR);
        this->skip(SEMICOLON);
    }
    std::cout << "const def end" << std::endl;
}

void Compiler::constState() {
    do {
        this->getSym();
        this->constDef();
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } while (this->sym == CONSTSYM);
}

void Compiler::getReturnType(int *returnType, std::string **name) {
    if (this->sym == INTSYM || this->sym == CHARSYM)
        *returnType = this->sym;
    else
        this->errorHandle(INTORCHARERROR);
    this->getSym();
    if (this->sym == ID) {
        *name = new std::string(this->token);
        this->getSym();
    } else {
        this->errorHandle(IDERROR);
        this->getSym();
    }
}

void Compiler::genTemp(std::string *temp) {
    std::stringstream stringStream = std::stringstream();
    stringStream << "$t";
    stringStream << this->temp++;
    *temp = stringStream.str();
    this->push(temp, INTSYM, SIMPLESYM, -1, this->line);
}

void Compiler::varDef(int returnType, std::string *name) {
    std::cout << "var def" << std::endl;
    symbol *sym = 0;
    if (this->find(name, &sym, true))
        this->errorHandle(DUPLICATEERROR);
    if (this->sym == SEMICOLON) {
        this->push(name, returnType, SIMPLESYM, -1, this->line);
        this->getSym();
        return;
    }
    if (this->sym == LBRACK) {
        std::cout << "var" << std::endl;
        int feature = -1;
        this->getSym();
        if (this->sym == UNSIGNEDINT) {
            feature = std::atoi(this->token.c_str());
            this->getSym();
        } else
            this->errorHandle(UNSIGNEDINTERROR);
        if (this->sym == RBRACK) {
            this->push(name, returnType, ARRAYSYM, feature, this->line);
            this->getSym();
        } else
            this->errorHandle(RBRACKERROR);
    } else {
        std::cout << "var" << std::endl;
        this->push(name, returnType, SIMPLESYM, -1, this->line);
    }

    while (this->sym == COMMA) {
        std::cout << "var" << std::endl;
        std::string *name2 = 0;
        this->getSym();
        if (this->sym == ID) {
            symbol *sym = 0;
            if (this->find(new std::string(this->token), &sym, true))
                this->errorHandle(DUPLICATEERROR);
            name2 = new std::string(this->token);
            this->getSym();
        } else
            this->errorHandle(IDERROR);
        int feature = -1;
        if (this->sym == LBRACK) {
            this->getSym();
            if (this->sym == UNSIGNEDINT) {
                feature = std::atoi(this->token.c_str());
                this->getSym();
            } else
                this->errorHandle(UNSIGNEDINTERROR);
            if (this->sym == RBRACK) {
                this->push(name2, returnType, ARRAYSYM, feature, this->line);
                this->getSym();
            } else
                this->errorHandle(RBRACKERROR);
        } else {
            this->push(name2, returnType, SIMPLESYM, -1, this->line);
        }
    }
    std::cout << "var def end" << std::endl;
    if (this->sym == SEMICOLON)
        this->getSym();
    else
        this->errorHandle(SEMICOLONERROR);
}

void Compiler::paraProcess(symbol *sym) {
    std::cout << "para process" << std::endl;
    std::string *name = 0;
    int returnType = NONE;
    this->getReturnType(&returnType, &name);
    if (!name) {
        name = new std::string();
        this->genTemp(name);
    }
    std::cout << "para" << std::endl;
    sym->paraList[sym->feature++] = returnType;
    symbol *temp = 0;
    if (this->find(name, &temp, true)) {
        this->errorHandle(DUPLICATEERROR);
        return;
    } else
        this->push(name, returnType, PARASYM, -1, this->line);
    while (this->sym == COMMA) {
        std::cout << "para" << std::endl;
        std::string *name = 0;
        int returnType = NONE;
        this->getSym();
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        sym->paraList[sym->feature++] = returnType;
        symbol *temp = 0;
        if (this->find(name, &temp, true)) {
            this->errorHandle(DUPLICATEERROR);
            return;
        } else
            this->push(name, returnType, PARASYM, -1, this->line);
    }
    std::cout << "para process end" << std::endl;
}

void Compiler::varState() {
    int returnType = NONE;
    std::string *name = 0;
    this->getReturnType(&returnType, &name);
    if (!name) {
        name = new std::string();
        this->genTemp(name);
    }
    if (this->isInTarget(VARDEF, VARDEF_SIZE))
        this->varDef(returnType, name);
    else {
        this->errorHandle(VARDEFERROR);
        this->skip(DEF, DEF_SIZE);
        return;
    }
    while (this->isInTarget(DEF, DEF_SIZE)) {
        int returnType = NONE;
        std::string *name = 0;
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        if (this->isInTarget(VARDEF, VARDEF_SIZE))
            this->varDef(returnType, name);
        else {
            this->errorHandle(VARDEFERROR);
            this->skip(DEF, DEF_SIZE);
            return;
        }
    }
}

bool Compiler::isOperandNum(std::string *s) {
    return s->length() > 0 ? (*s)[0] >= '0' && (*s)[0] <= '9' || (*s)[0] == '-' : false;
}

void Compiler::paraListProcess(symbol *sym) {
    int type = NONE;
    int index = 0;
    std::string para = std::string();
    this->expressionProcess(&type, &para);
    //todo
    if (sym->feature > index) {
        if (sym->paraList[index] != type)
            this->errorHandle(PARATYPEERROR);
    } else {
        this->errorHandle(PARANUMERROR);
        this->skip(RPARENT);
        return;;
    }
    index++;
    while (this->sym == COMMA) {
        int type = NONE;
        this->getSym();
        std::string para = std::string();
        this->expressionProcess(&type, &para);
        //todo
        if (sym->feature > index) {
            if (sym->paraList[index] != type)
                this->errorHandle(PARATYPEERROR);
        } else {
            this->errorHandle(PARANUMERROR);
            this->skip(RPARENT);
            return;;
        }
        index++;
    }
    if (index != sym->feature) {
        this->errorHandle(PARANUMERROR);
        this->skip(RPARENT);
        return;
    }
}

void Compiler::int2String(std::string *s, int value) {
    std::stringstream ss = std::stringstream();
    ss << value;
    *s = ss.str();
}

void Compiler::constProcess(int *value, int *returnType) {
    if (this->sym == CHAR) {
        *returnType = CHAR;
        *value = this->token[0];
        this->getSym();
    } else {
        *returnType = INTSYM;
        this->constructInt(value);
    }
}

void Compiler::factorProcess(int *resultType, std::string *operand) {
    if (this->sym == ID) {
        symbol *sym = 0;
        if (!this->find(new std::string(this->token), &sym, false)) {
            this->errorHandle(IDDEFINEERROR);
            this->skip(FACTOR, FACTOR_SIZE);
            return;
        }
        *resultType = sym->returnType;
        this->getSym();
        if (this->sym == LBRACK) {
            if (sym->symbolType != ARRAYSYM)
                this->errorHandle(ARRAYERROR);
            int type = NONE;
            this->getSym();
            std::string temp = std::string();
            this->expressionProcess(&type, &temp);
            if (type != INTSYM)
                this->errorHandle(INTEXPERROR);
            if (this->isOperandNum(&temp)) {
                int constValue = atoi(temp.c_str());
                if (constValue >= sym->feature || constValue < 0)
                    this->errorHandle(ARRAYOUTERROR);
            }
            this->genTemp(operand);
            //todo push midcode
            if (this->sym == RBRACK)
                this->getSym();
            else
                this->errorHandle(RBRACKERROR);
        } else if (this->sym == LPARENT) {
            if (sym->symbolType != FUNCSYM) {
                this->errorHandle(FUNCERROR);
                return;;
            }
            if (sym->returnType == VOIDSYM)
                this->errorHandle(RETURNFUNCERROR);
            this->getSym();
            this->paraListProcess(sym);
            if (this->sym == RPARENT) {
                //todo
                *operand = std::string("#RET");
                this->getSym();
            } else
                this->errorHandle(RPARENTERROR);
        } else {
            if (sym->symbolType == SIMPLESYM || sym->symbolType == PARASYM)
                *operand = *sym->name;
            else if (sym->symbolType == FUNCSYM) {
                if (sym->feature != 0)
                    this->errorHandle(NOPARAFUNCERROR);
                //todo
                *operand = std::string("#RET");
            } else if (sym->symbolType == CONSTSYM) {
                int value = sym->feature;
                std::string constValue = std::string();
                this->int2String(&constValue, value);
                *operand = constValue;
            } else
                this->errorHandle(IDUSEERROR);
        }
    } else if (this->sym == LPARENT) {
        this->getSym();
        this->expressionProcess(resultType, operand);
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
    } else if (this->isInTarget(CONST, CONST_SIZE)) {
        int value;
        this->constProcess(&value, resultType);
        std::string constValue = std::string();
        this->int2String(&constValue, value);
        *operand = constValue;
    } else {
        this->errorHandle(FACTORERROR);
        this->skip(FACTOR, FACTOR_SIZE);
    }
}

bool Compiler::isOperandReturn(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '#' : false;
}

bool Compiler::isOperandTemp(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '$' : false;
}

void Compiler::termProcess(int *resultType, std::string *operand) {
    std::string operand1 = std::string();
    this->factorProcess(resultType, &operand1);
    if (this->isOperandReturn(&operand1)) {
        std::string temp = std::string();
        this->genTemp(&temp);
        //todo
        operand1 = temp;
    }
    while (this->sym == MULTI || this->sym == DIVIDE) {
        *resultType = INTSYM;
        bool flag = this->sym == MULTI;
        int fact = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->factorProcess(&fact, &operand2);
        if (this->isOperandNum(&operand1)) {
            if (this->isOperandNum(&operand2)) {
                int op1 = atoi(operand1.c_str());
                int op2 = atoi(operand2.c_str());
                if (op2 == 0 && !flag) {
                    this->errorHandle(ZEROERROR);
                    op2 += 1;
                }
                int result = flag ? op1 * op2 : op1 / op2;
                std::string constValue = std::string();
                this->int2String(&constValue, result);
                operand1 = constValue;
            } else {
                if (!this->isOperandTemp(&operand2)) {
                    std::string result = std::string();
                    this->genTemp(&result);
                    //todo
                    operand1 = result;
                } else {
                    //todo
                    operand1 = operand2;
                }
            }
        } else {
            if (this->isOperandNum(&operand2)) {
                int op2 = atoi(operand2.c_str());
                if (op2 == 0 && !flag)
                    this->errorHandle(ZEROERROR);
            }
            if (this->isOperandTemp(&operand1)) {
                //todo
            } else {
                std::string result = std::string();
                this->genTemp(&result);
                //todo
                operand1 = result;
            }
        }
    }
    *operand = operand1;
}

bool Compiler::isOperandId(std::string *s) {
    return s->length() > 0 ? (*s)[0] == '-' || ((*s)[0] >= 'A' && (*s)[0] <= 'Z') || ((*s)[0] >= 'a' && (*s)[0] <= 'z')
                           : false;
}

void Compiler::expressionProcess(int *resultType, std::string *operand) {
    std::string operand1 = std::string();
    bool flag1 = false;
    bool flag2 = false;
    if (this->sym == PLUS || this->sym == MINUS) {
        flag1 = true;
        flag2 = this->sym == MINUS;
        this->getSym();
    }
    this->termProcess(resultType, &operand1);
    if (flag2) {
        if (this->isOperandNum(&operand1)) {
            int value = -atoi(operand1.c_str());
            std::string constValue = std::string();
            this->int2String(&constValue, value);
            operand1 = constValue;
        } else if (this->isOperandId(&operand1)) {
            std::string temp = std::string();
            this->genTemp(&temp);
            //todo
            operand1 = temp;
        } else {
            //todo
        }
    }
    *resultType = flag1 ? INTSYM : *resultType;
    while (this->sym == PLUS || this->sym == MINUS) {
        bool flag3 = this->sym == PLUS;
        int result = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->termProcess(&result, &operand2);
        *resultType = INTSYM;
        if (this->isOperandNum(&operand1)) {
            if (this->isOperandNum(&operand2)) {
                int op1 = atoi(operand1.c_str());
                int op2 = atoi(operand2.c_str());
                int result = flag3 ? op1 + op2 : op1 - op2;
                std::string constValue = std::string();
                this->int2String(&constValue, result);
                operand1 = constValue;
            } else {
                if (this->isOperandId(&operand2)) {
                    std::string temp = std::string();
                    this->genTemp(&temp);
                    //todo
                    operand1 = temp;
                } else {
                    //todo
                    operand1 = operand2;
                }
            }
        } else {
            if (this->isOperandTemp(&operand1)) {
                //todo
            } else {
                std::string temp = std::string();
                this->genTemp(&temp);
                //todo
                operand1 = temp;
            }
        }
    }
    *operand = operand1;
}

void Compiler::genLabel(std::string *label) {
    std::stringstream stringStream = std::stringstream();
    stringStream << "$label";
    stringStream << this->label++;
    *label = stringStream.str();
}

void Compiler::conditionProcess(std::string *label) {
    std::cout << "condition statement" << std::endl;
    int returnType = NONE;
    std::string operand1 = std::string();
    this->expressionProcess(&returnType, &operand1);
    if (this->isInTarget(RELATION, RELATION_SIZE)) {
        int relation = this->sym;
        int returnType2 = NONE;
        std::string operand2 = std::string();
        this->getSym();
        this->expressionProcess(&returnType2, &operand2);
        //todo
    } else {
        //todo
    }
}

void Compiler::ifProcess(bool *flag, int returnType, std::string *name) {
    std::cout << "if statement" << std::endl;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    std::string *elseLabel = new std::string();
    this->genLabel(elseLabel);
    std::string *endLabel = new std::string();
    this->genLabel(endLabel);
    this->conditionProcess(elseLabel);
    if (this->sym == RPARENT)
        this->getSym();
    else {
        this->errorHandle(RPARENTERROR);
        this->skip(STATEMENT, STATEMENT_SIZE);
    }
    if (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
    else
        this->errorHandle(STATEMENTERROR);
    //todo
    if(this->sym == ELSESYM) {
        std::cout << "else statement" << std::endl;
        this->getSym();
        if(this->isInTarget(STATEMENT,STATEMENT_SIZE))
            this->statementProcess(flag,returnType,name);
        else{
            this->errorHandle(STATEMENTERROR);
            this->skip(STATEMENT,STATEMENT_SIZE);
        }
    }
    else
        this->skip(STATEMENT,STATEMENT_SIZE);
}

void Compiler::scanfProcess() {
    std::cout << "scanf" << std::endl;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    if (this->sym == ID) {
        symbol *sym = 0;
        if (!this->find(new std::string(this->token), &sym, false)) {
            this->errorHandle(IDDEFINEERROR);
            this->skip(SEMICOLON);
            return;
        }
        if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
            this->errorHandle(SIMPLEVARERROR);
        switch (sym->returnType) {
            case INTSYM:
                //todo
                break;
            case CHARSYM:
                //todo
                break;
        }
        this->getSym();
    } else {
        this->errorHandle(IDERROR);
        this->skip(END, END_SIZE);
        return;
    }
    while (this->sym == COMMA) {
        this->getSym();
        if (this->sym == ID) {
            symbol *sym = 0;
            if (!this->find(new std::string(this->token), &sym, false)) {
                this->errorHandle(IDDEFINEERROR);
                this->skip(SEMICOLON);
                return;
            }
            if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
                this->errorHandle(SIMPLEVARERROR);
            switch (sym->returnType) {
                case INTSYM:
                    //todo
                    break;
                case CHARSYM:
                    //todo
                    break;
            }
            this->getSym();
        } else {
            this->errorHandle(IDERROR);
            this->skip(END, END_SIZE);
            continue;
        }
    }
    if (this->sym == RPARENT)
        this->getSym();
    else
        this->errorHandle(RPARENTERROR);
}

void Compiler::printfProcess() {
    std::cout << "printf" << std::endl;
    std::string *num = 0;
    this->getSym();
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    if (this->sym == STRING) {
        int index = -1;
        this->pushString(new std::string(this->token), &index);
        num = new std::string();
        this->int2String(num, index);
        this->getSym();
        if (this->sym == COMMA)
            this->getSym();
        else {
            if (this->sym == RPARENT)
                this->getSym();
            else
                this->errorHandle(RPARENTERROR);
            //todo
            return;
        }
    }
    int returnType = NONE;
    std::string temp = std::string();
    this->expressionProcess(&returnType, &temp);
    if (num) {
        //todo
    }
    switch (returnType) {
        case INTSYM:
            //todo
            break;
        case CHARSYM:
            //todo
            break;
    }
    if (this->sym == RPARENT)
        this->getSym();
    else {
        this->errorHandle(RPARENTERROR);
        this->skip(SEMICOLON);
    }
}

void Compiler::returnProcess(bool *flag, int returnType, std::string *name) {
    std::cout << "return" << std::endl;
    this->getSym();
    if (this->sym == LPARENT) {
        this->getSym();
        int returnType2 = NONE;
        std::string temp = std::string();
        this->expressionProcess(&returnType2, &temp);
        if (returnType == VOIDSYM)
            this->errorHandle(RETURNEXTRAERROR);
        else {
            if (this->isOperandTemp(&temp)) {
                //todo
            } else {
                //todo
            }
            if (returnType != returnType2)
                this->errorHandle(RETURNERROR);
        }
        *flag = true;
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
    }
    if (returnType != VOIDSYM && !(*flag))
        this->errorHandle(RETURNERROR);
    //todo
}

void Compiler::doWhileProcess(bool *flag, int returnType, std::string *name) {
    std::cout << "do statement" << std::endl;
    std::string *doLabel = new std::string();
    std::string *endLabel = new std::string();
    this->genLabel(doLabel);
    this->genLabel(endLabel);
    //todo
    this->getSym();
    if (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
    else
        this->errorHandle(STATEMENTERROR);
    if (this->sym == WHILESYM) {
        std::cout << "while statement" << std::endl;
        this->getSym();
        if (this->sym == LPARENT)
            this->getSym();
        else
            this->errorHandle(LPARENTERROR);
        this->conditionProcess(endLabel);
        if (this->sym == RPARENT)
            this->getSym();
        else {
            this->errorHandle(RBRACEERROR);
            this->skip(STATEMENT, STATEMENT_SIZE);
        }
        //todo
    } else
        this->errorHandle(NOWHILEERROR);
}

void Compiler::forProcess(bool *flag, int returnType, std::string *name) {
    std::cout << "for statement" << std::endl;
    std::string *doLabel = new std::string();
    std::string *endLabel = new std::string();
    this->genLabel(doLabel);
    this->genLabel(endLabel);
    this->getSym();
    if (this->sym == LPARENT) {
        this->getSym();
        if (this->sym == ID) {
            this->reassignProcess(flag, returnType, new std::string(this->token));
        } else {
            this->errorHandle(IDERROR);
            this->skip(SEMICOLON);
        }
        this->conditionProcess(endLabel);
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
        if (this->sym == ID) {
            this->reassignProcess(flag, returnType, new std::string(this->token));
        } else {
            this->errorHandle(IDERROR);
            this->skip(SEMICOLON);
        }
        if(this->sym == RPARENT)
            this->getSym();
        else {
            this->errorHandle(RPARENTERROR);
            this->skip(STATEMENT,STATEMENT_SIZE);
        }
        this->statementProcess(flag, returnType, name);
    } else
        this->errorHandle(LPARENTERROR);
    std::cout << "for statement end" << std::endl;
}

void Compiler::reassignProcess(bool *flag, int returnType, std::string *name) {
    symbol *sym = 0;
    if (!this->find(name, &sym, false)) {
        this->errorHandle(IDDEFINEERROR);
        this->skip(SEMICOLON);
        return;
    }
    this->getSym();
    if (this->sym == LPARENT) {
        std::cout << "func statement" << std::endl;
        if (sym->symbolType != FUNCSYM)
            this->errorHandle(FUNCERROR);
        this->getSym();
        this->paraListProcess(sym);
        //todo
        if (this->sym == RPARENT)
            this->getSym();
        else
            this->errorHandle(RPARENTERROR);
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } else if (this->sym == ASSIGN) {
        std::cout << "assign statement" << std::endl;
        if (sym->symbolType != SIMPLESYM && sym->symbolType != PARASYM)
            this->errorHandle(SIMPLEVARERROR);
        this->getSym();
        int returnType2 = NONE;
        std::string operand = std::string();
        this->expressionProcess(&returnType2, &operand);
        if (sym->returnType == CHARSYM && returnType2 == INTSYM)
            this->errorHandle(ILLEGALASSERROR);
        if (this->isOperandTemp(&operand)) {
            //todo
        } else {
            //todo
        }
        if (this->sym == SEMICOLON)
            this->getSym();
        else this->errorHandle(SEMICOLON);
    } else if (this->sym == LBRACK) {
        std::cout << "assign statement" << std::endl;
        if (sym->symbolType != ARRAYSYM)
            this->errorHandle(ARRAYERROR);
        this->getSym();
        int returnType2 = NONE;
        std::string operand = std::string();
        this->expressionProcess(&returnType2, &operand);
        if (this->isOperandNum(&operand)) {
            int index = atoi(operand.c_str());
            if (index >= sym->feature)
                this->errorHandle(ARRAYOUTERROR);
        }
        if (this->sym == RBRACK)
            this->getSym();
        else
            this->errorHandle(RBRACKERROR);
        if (this->sym == ASSIGN)
            this->getSym();
        else
            this->errorHandle(ASSIGNERROR);
        int returnType3 = NONE;
        std::string operand2 = std::string();
        this->expressionProcess(&returnType3, &operand2);
        if (sym->returnType == CHARSYM && returnType3 == INTSYM)
            this->errorHandle(ILLEGALASSERROR);
        //todo
        if (this->sym == SEMICOLON)
            this->getSym();
        else
            this->errorHandle(SEMICOLONERROR);
    } else if (this->sym == SEMICOLON) {
        if (sym->symbolType != FUNCSYM || sym->feature != 0)
            this->errorHandle(NOPARAFUNCERROR);
        //todo
        this->getSym();
    } else
        this->errorHandle(SEMICOLONERROR);
}

void Compiler::statementProcess(bool *flag, int returnType, std::string *funcName) {
    std::string *name = new std::string(this->token);
    switch (this->sym) {
        case IFSYM:
            this->ifProcess(flag, returnType, funcName);
            break;
        case DOSYM:
            this->doWhileProcess(flag, returnType, funcName);
            break;
        case FORSYM:
            this->forProcess(flag,returnType,funcName);
            break;
        case SCANFSYM:
            this->scanfProcess();
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            break;
        case PRINTFSYM:
            this->printfProcess();
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            break;
        case RETURNSYM:
            this->returnProcess(flag, returnType, funcName);
            if (this->sym == SEMICOLON)
                this->getSym();
            else
                this->errorHandle(SEMICOLONERROR);
            break;
        case LBRACE:
            this->getSym();
            this->statementsProcess(flag, returnType, funcName);
            if (this->sym == RBRACE)
                this->getSym();
            else
                this->errorHandle(RBRACEERROR);
            break;
        case ID:
            this->reassignProcess(flag, returnType, name);
            break;
        case SEMICOLON:
            this->getSym();
            break;
    }
}

void Compiler::statementsProcess(bool *flag, int returnType, std::string *name) {
    while (this->isInTarget(STATEMENT, STATEMENT_SIZE))
        this->statementProcess(flag, returnType, name);
}

void Compiler::compoundProcess(bool *flag, int returnType, std::string *name) {
    if (this->sym == CONSTSYM)
        this->constState();
    if (this->isInTarget(DEF, DEF_SIZE))
        this->varState();
    this->statementsProcess(flag, returnType, name);

}

void Compiler::noParaFuncDef(symbol *sym) {
    if (this->sym == LBRACE)
        this->getSym();
    else
        this->errorHandle(LBRACEERROR);
    bool flag = false;
    //todo pushmidcode
    this->compoundProcess(&flag, sym->returnType, sym->name);
    if (this->sym == RBRACE) {
        this->getSym();
        if (!flag && sym->returnType != VOIDSYM)
            this->errorHandle(RETURNMISSERROR);
    } else
        this->errorHandle(RBRACEERROR);
    //todo
}

void Compiler::paraFuncDef(symbol *sym) {
    std::cout << "func def" << std::endl;
    this->getSym();
    if(this->sym != RPARENT)
        this->paraProcess(sym);
    if (this->sym == RPARENT)
        this->getSym();
    else
        this->errorHandle(RPARENTERROR);
    this->noParaFuncDef(sym);
    std::cout << "func def end" << std::endl;
}

void Compiler::voidFuncDef() {
    int returnType = VOIDSYM;
    std::string *name = new std::string(this->token);
    symbol *sym = 0;
    if (this->find(name, &sym, true))
        this->errorHandle(DUPLICATEERROR);
    else
        sym = this->push(name, returnType, FUNCSYM, 0, this->line);
    this->getSym();
    this->prepareFunc();
    if (this->sym == LPARENT)
        this->paraFuncDef(sym);
    else
        this->noParaFuncDef(sym);
    this->pop();
}

void Compiler::mainDef() {
    std::cout << "main" << std::endl;
    std::string *name = new std::string("main");
    if (this->sym == MAINSYM)
        this->getSym();
    else {
        this->errorHandle(MAINERROR);
        this->getSym();
    }
    this->push(name, VOIDSYM, FUNCSYM, 0, this->line);
    if (this->sym == LPARENT)
        this->getSym();
    else
        this->errorHandle(LPARENTERROR);
    if (this->sym == RPARENT)
        this->getSym();
    else
        this->errorHandle(RPARENTERROR);
    if (this->sym == LBRACE) {
        this->prepareFunc();
        this->getSym();
    } else
        this->errorHandle(LBRACEERROR);
    bool flag = false;
    //todo
    this->compoundProcess(&flag, VOIDSYM, name);
    if (this->sym == RBRACE) {
        this->pop();
        //todo
        return;
    } else
        this->errorHandle(RBRACEERROR);
}

void Compiler::afterVar() {
    if (this->sym == VOIDSYM) {
        this->getSym();
        if (this->sym == ID) {
            this->voidFuncDef();
            this->afterVar();
        } else
            this->mainDef();
    }
    else{
        std::string *name = 0;
        int returnType = NONE;
        symbol *sym = 0;
        this->getReturnType(&returnType,&name);
        if(!name){
            name = new std::string();
            this->genTemp(name);
        }
        if(this->find(name,&sym,true))
            this->errorHandle(DUPLICATEERROR);
        else
            sym = this->push(name,returnType,FUNCSYM,0,this->line);
        this->prepareFunc();
        if(this->sym == LPARENT)
            this->paraFuncDef(sym);
        else
            this->noParaFuncDef(sym);
        this->pop();
        this->afterVar();
    }
}

void Compiler::afterConst() {
    if (this->sym == VOIDSYM) {
        this->getSym();
        if (this->sym == ID) {
            this->voidFuncDef();
            this->afterVar();
        } else
            this->mainDef();
    } else {
        std::string *name = 0;
        int returnType = 0;
        symbol *sym = 0;
        this->getReturnType(&returnType, &name);
        if (!name) {
            name = new std::string();
            this->genTemp(name);
        }
        if (this->isInTarget(VARDEF, VARDEF_SIZE)) {
            this->varDef(returnType, name);
            this->afterConst();
        } else if (this->sym == LPARENT) {
            symbol *sym = 0;
            if (this->find(name, &sym, true))
                this->errorHandle(DUPLICATEERROR);
            else
                sym = this->push(name, returnType, FUNCSYM, 0, this->line);
            this->prepareFunc();
            this->paraFuncDef(sym);
            this->pop();
            this->afterVar();
        } else {
            symbol *sym = 0;
            if (this->find(name, &sym, true))
                this->errorHandle(DUPLICATEERROR);
            else
                sym = this->push(name, returnType, FUNCSYM, 0, this->line);
            this->prepareFunc();
            this->paraFuncDef(sym);
            this->pop();
            this->afterVar();
        }
    }
}

void Compiler::analyze() {
    std::cout << "syntax analyze start" << std::endl;
    this->getSym();
    if (this->sym == CONSTSYM) this->constState();
    this->afterConst();
    std::cout << "syntax analyze end" << std::endl;
}