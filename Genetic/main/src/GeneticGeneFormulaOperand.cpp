#include "Debug/main/inc/Logger.hpp"
#include "Genetic/main/inc/GeneticGeneFormulaOperand.hpp"
#include "Genetic/main/inc/GeneticGeneTreeBranch.hpp"
#include "Misc/main/inc/Misc.hpp"

static std::vector<CObject *> _dummy;
std::vector<CObject *> & dummy = _dummy;

GeneticGeneFormulaOperand::GeneticGeneFormulaOperand()
    : GeneticGeneTreeBranch(dummy) {
    Logger::trace(std::string("GeneticGeneFormulaOperand::GeneticGeneFormulaOperand()>"));

    for (auto & ope : mapNbOperand) {
        Logger::trace(ope.first.toString() + std::string(" : ") + ope.second.toString() + std::string(" "));
    }
}

GeneticGeneFormulaOperand::~GeneticGeneFormulaOperand() {
    Logger::trace(std::string("GeneticGeneFormulaOperand::~GeneticGeneFormulaOperand()<"));
}

void GeneticGeneFormulaOperand::addOperator(CString ope, CInteger nbOperand) {
    listOperatorPossible.push_back(ope);
    mapNbOperand[ope] = nbOperand;
}

void GeneticGeneFormulaOperand::addOperand(CInteger operand) {
    listOperandPossible.push_back(operand);
}

GeneticGeneFormulaOperand * GeneticGeneFormulaOperand::clone() { /*const*/
    GeneticGeneFormulaOperand * geneFormulaOperand = new GeneticGeneFormulaOperand();

    for (auto c : code) {
        geneFormulaOperand->code.push_back(c);
    }

    for (auto branch : listBranch) {
        GeneticGeneTreeBranch * op2 = branch->clone();
        op2->setParent(geneFormulaOperand);
        geneFormulaOperand->listBranch.push_back(op2);
    }

    return geneFormulaOperand;
}

bool GeneticGeneFormulaOperand::equals(const GeneticGene & /*other*/) const {
    Logger::error(std::string("GeneticGeneFormulaOperand::equals(): returning false in all cases"));
    return false;
}

CInteger GeneticGeneFormulaOperand::getNbOperandForOperator(CString ope) {
    return mapNbOperand[ope];
}

bool GeneticGeneFormulaOperand::isOperator() const {
    bool result = false;

    if (code.size() > 0) {
        const auto search = std::find(listOperatorPossible.begin(), listOperatorPossible.end(), *code[0]);

        if (search != listOperatorPossible.end()) {
            result = true;
        }
    }

    return result;
}

void GeneticGeneFormulaOperand::mutate() {
    GeneticGeneTreeBranch::mutate();
    repareGene();
}

GeneticGeneFormulaOperand * GeneticGeneFormulaOperand::randomGene() {
    Logger::trace(std::string("GeneticGeneFormulaOperand::randomGene()>"));

    code.clear();

    if (Misc::random(50)) {
        code.push_back(&listOperatorPossible[Misc::random(0, listOperatorPossible.size() - 1)]);
    }
    else {
        code.push_back(&listOperandPossible[Misc::random(0, listOperandPossible.size() - 1)]);
    }

    repareGene();
    return this;
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

    for (auto gene : listOld) {
        gene->setParent(nullptr);
    }

    for (auto gene : listBranch) {
        gene->setParent(this);
    }
}

std::vector<CInteger> GeneticGeneFormulaOperand::listOperandPossible = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

std::vector<CString> GeneticGeneFormulaOperand::listOperatorPossible = {
    std::string("+"),
    std::string("-"),
    std::string("*"),
    std::string("/"),
    std::string("sqrt"),
    std::string("^2")
};

std::map<CString, CInteger, CString::Compare> GeneticGeneFormulaOperand::mapNbOperand = {
    {std::string("+"), 2},
    {std::string("-"), 2},
    {std::string("*"), 2},
    {std::string("/"), 2},
    {std::string("sqrt"), 1},
    {std::string("^2"), 1}
};
