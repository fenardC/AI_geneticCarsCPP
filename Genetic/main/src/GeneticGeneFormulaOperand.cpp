
#include "Genetic/main/inc/GeneticGeneFormulaOperand.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "CObject/main/inc/CInteger.hpp"
#include "Misc/main/inc/Misc.hpp"


static std::vector<CInteger> initlistOperandPossible();
static std::vector<std::string> initListOperatorPossible();
static std::map<std::string, CInteger> initMapNbOperand();

static std::vector<CInteger> initlistOperandPossible() {
    std::vector<CInteger> result;
    result.push_back(CInteger(1));
    result.push_back(CInteger(2));
    result.push_back(CInteger(3));
    result.push_back(CInteger(4));
    result.push_back(CInteger(5));
    result.push_back(CInteger(6));
    result.push_back(CInteger(7));
    result.push_back(CInteger(8));
    result.push_back(CInteger(9));
    result.push_back(CInteger(10));

    return result;
}

static std::vector<std::string> initListOperatorPossible() {
    std::vector<std::string> result;
    result.push_back(std::string("+"));
    result.push_back(std::string("-"));
    result.push_back(std::string("*"));
    result.push_back(std::string("/"));
    result.push_back(std::string("sqrt"));
    result.push_back(std::string("^2"));

    return result;
}

static std::map<std::string, CInteger> initMapNbOperand() {
    const CInteger oneOperand(1);
    const CInteger twoOperands(2);
    std::map<std::string, CInteger> result;

    result[std::string("+")] = twoOperands;
    result[std::string("-")] = twoOperands;
    result[std::string("*")] = twoOperands;
    result[std::string("/")] = twoOperands;
    result[std::string("sqrt")] = oneOperand;
    result[std::string("^2")] = oneOperand;

    return result;
}

static std::vector<CObject *> _dummy;
std::vector<CObject *> & dummy = _dummy;

GeneticGeneFormulaOperand::GeneticGeneFormulaOperand()
    : GeneticGeneTreeBranch(dummy) {
}

GeneticGeneFormulaOperand::~GeneticGeneFormulaOperand() {

}

GeneticGeneFormulaOperand * GeneticGeneFormulaOperand::clone() { /*const*/
    GeneticGeneFormulaOperand * geneFormulaOperand = new GeneticGeneFormulaOperand();

    for (CObject * c : code) {
        geneFormulaOperand->code.push_back(c);
    }

    for (GeneticGeneTreeBranch * branch : listBranch) {
        GeneticGeneTreeBranch * op2 = branch->clone();
        op2->setParent(geneFormulaOperand);
        geneFormulaOperand->listBranch.push_back(op2);
    }

    return geneFormulaOperand;
}

GeneticGeneFormulaOperand * GeneticGeneFormulaOperand::randomGene() {
    code.clear();

    if (Misc::random(50)) {
#warning TO BE DONE
#if 0
        code.push_back(listOperatorPossible[Misc::random(0, listOperatorPossible.size() - 1)]);
#endif
    }
    else {
#warning TO BE DONE
#if 0
        code.push_back(listOperandPossible[Misc::random(0, listOperandPossible.size() - 1)]);
#endif
    }

    repareGene();
    return this;
}

void GeneticGeneFormulaOperand::mutate() {
    GeneticGeneTreeBranch::mutate();
    repareGene();
}

void GeneticGeneFormulaOperand::repareGene() {
    std::vector<GeneticGeneTreeBranch *> listOld = listBranch;

#warning TO BE DONE

#if 0

    if (isOperator()) {
        int nb = getNbOperandForOperator(code[0]) - listBranch.size();

        if (nb > 0) {
            for (int i = 0 ; i < nb ; i++) {
                GeneticGeneFormulaOperand * p = new GeneticGeneFormulaOperand();
                listBranch.push_back(p->randomGene());
            }
        }
        else {
            for (int i = 0 ; i < -nb ; i++) {
                listBranch.erase(listBranch.begin() + Misc::random(0, listBranch.size() - 1));
            }
        }
    }
    else {
        listBranch.clear();
    }

#endif

    for (GeneticGeneTreeBranch * gene : listOld) {
        gene->setParent(nullptr);
    }

    for (GeneticGeneTreeBranch * gene : listBranch) {
        gene->setParent(this);
    }
}

bool GeneticGeneFormulaOperand::isOperator() const {
    bool result = false;

#warning TO BE DONE

#if 0

    if (code.size() > 0) {
        const auto search = std::find(listOperatorPossible.begin(), listOperatorPossible.end(), code[0]);

        if (search != listOperatorPossible.end()) {
            result = true;
        }
    }

#endif
    return result;
}

CInteger GeneticGeneFormulaOperand::getNbOperandForOperator(std::string ope) {
    return mapNbOperand[ope];
}

void GeneticGeneFormulaOperand::addOperator(std::string ope, CInteger nbOperand) {
    listOperatorPossible.push_back(ope);
    mapNbOperand[ope] = nbOperand;
}

void GeneticGeneFormulaOperand::addOperand(CInteger operand) {
    listOperandPossible.push_back(operand);
}

std::vector<CInteger> GeneticGeneFormulaOperand::listOperandPossible = initlistOperandPossible();

std::vector<std::string> GeneticGeneFormulaOperand::listOperatorPossible = initListOperatorPossible();

std::map<std::string, CInteger> GeneticGeneFormulaOperand::mapNbOperand = initMapNbOperand();
