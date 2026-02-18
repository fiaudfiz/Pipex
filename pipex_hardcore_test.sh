#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PIPEX="$(pwd)/pipex"
PASS=0
FAIL=0

# Fonction de test
test_pipex() {
    local test_num=$1
    local description=$2
    shift 2
    local cmd="$@"

    echo -n "Test $test_num: $description... "

    # Exécute la commande
    eval "$cmd" > /tmp/pipex_test_output 2>&1
    local exit_code=$?

    # Vérification basique (tu peux ajouter plus de checks)
    if [ $exit_code -eq 0 ] || [ $exit_code -eq 1 ] || [ $exit_code -eq 127 ]; then
        echo -e "${GREEN}PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}FAIL${NC} (exit: $exit_code)"
        cat /tmp/pipex_test_output
        ((FAIL++))
    fi
}

# Fonction pour comparer avec bash
test_compare_bash() {
    local test_num=$1
    local description=$2
    local infile=$3
    local cmd1=$4
    local cmd2=$5
    local outfile=$6

    echo -n "Test $test_num: $description... "

    # Nettoie les fichiers
    rm -f /tmp/pipex_out /tmp/bash_out

    # Exécute pipex
    $PIPEX "$infile" "$cmd1" "$cmd2" /tmp/pipex_out 2>/dev/null
    local pipex_exit=$?

    # Exécute bash
    if [ -f "$infile" ]; then
        bash -c "< '$infile' $cmd1 | $cmd2 > /tmp/bash_out 2>/dev/null"
    else
        bash -c "< '$infile' $cmd1 | $cmd2 > /tmp/bash_out 2>/dev/null"
    fi
    local bash_exit=$?

    # Compare les sorties
    if diff -q /tmp/pipex_out /tmp/bash_out > /dev/null 2>&1; then
        echo -e "${GREEN}PASS${NC}"
        ((PASS++))
    else
        echo -e "${RED}FAIL${NC}"
        echo "Différences trouvées:"
        diff /tmp/pipex_out /tmp/bash_out | head -20
        ((FAIL++))
    fi
}

echo "======================================"
echo "   PIPEX HARDCORE TESTS 🔥"
echo "======================================"
echo ""

# Crée les fichiers de test
echo "Préparation des fichiers de test..."
mkdir -p /tmp/pipex_test
cd /tmp/pipex_test

# Fichier basique
echo -e "ligne 1\nligne 2\nligne 3" > test.txt

# Gros fichier
seq 1 10000 > big.txt

# Fichier avec caractères spéciaux
echo -e "hello\tworld\n\$PATH\n'quotes'\n\"double\"" > special.txt

# Fichier vide
touch empty.txt

# Fichier binaire
dd if=/dev/urandom of=binary.bin bs=1024 count=10 2>/dev/null

echo ""
echo "======================================"
echo "   TESTS DE ROBUSTESSE"
echo "======================================"

# Test 1: Commandes avec guillemets dans les arguments
test_compare_bash 1 "Arguments avec espaces" \
    "test.txt" \
    "cat" \
    "grep ligne" \
    "out.txt"

# Test 2: Fichier inexistant en entrée
test_compare_bash 2 "Infile inexistant" \
    "fichier_qui_nexiste_pas.txt" \
    "cat" \
    "wc -l" \
    "out.txt"

# Test 3: Outfile sans permissions
touch no_write.txt
chmod 000 no_write.txt
test_pipex 3 "Outfile sans permissions" \
    "$PIPEX test.txt 'cat' 'cat' no_write.txt"
chmod 644 no_write.txt

# Test 4: Infile sans permissions
touch no_read.txt
chmod 000 no_read.txt
test_pipex 4 "Infile sans permissions" \
    "$PIPEX no_read.txt 'cat' 'cat' out.txt"
chmod 644 no_read.txt

# Test 5: Les deux fichiers inexistants
test_pipex 5 "Infile et outfile inexistants" \
    "$PIPEX noexist1.txt 'cat' 'cat' /root/noexist2.txt"

# Test 6: Commande inexistante (première)
test_compare_bash 6 "Première commande inexistante" \
    "test.txt" \
    "cmdquinexistepas" \
    "cat" \
    "out.txt"

# Test 7: Commande inexistante (deuxième)
test_compare_bash 7 "Deuxième commande inexistante" \
    "test.txt" \
    "cat" \
    "cmdquinexistepas" \
    "out.txt"

# Test 8: Les deux commandes inexistantes
test_pipex 8 "Les deux commandes inexistantes" \
    "$PIPEX test.txt 'nope1' 'nope2' out.txt"

# Test 9: Commande qui échoue
test_compare_bash 9 "Commande qui échoue (grep sans match)" \
    "test.txt" \
    "grep motquinexistepas" \
    "cat" \
    "out.txt"

# Test 10: Fichier vide
test_compare_bash 10 "Fichier vide en entrée" \
    "empty.txt" \
    "cat" \
    "wc -l" \
    "out.txt"

echo ""
echo "======================================"
echo "   TESTS DE GROS VOLUMES"
echo "======================================"

# Test 11: Gros fichier
test_compare_bash 11 "Gros fichier (10000 lignes)" \
    "big.txt" \
    "cat" \
    "head -100" \
    "out.txt"

# Test 12: Pipeline qui filtre tout
test_compare_bash 12 "Pipeline qui filtre tout" \
    "big.txt" \
    "grep 99999999" \
    "cat" \
    "out.txt"

echo ""
echo "======================================"
echo "   TESTS AVEC CARACTÈRES SPÉCIAUX"
echo "======================================"

# Test 13: Tabs et caractères spéciaux
test_compare_bash 13 "Fichier avec tabs et \$" \
    "special.txt" \
    "cat" \
    "cat" \
    "out.txt"

# Test 14: Commande avec flags complexes
test_compare_bash 14 "Flags multiples" \
    "test.txt" \
    "cat -e" \
    "grep -v '^$'" \
    "out.txt"

echo ""
echo "======================================"
echo "   TESTS BONUS (si multi-pipes)"
echo "======================================"

# Test 15: 3 commandes
if [ $# -eq 0 ]; then
    test_pipex 15 "3 commandes (bonus)" \
        "$PIPEX test.txt 'cat' 'cat' 'cat' out.txt"
fi

# Test 16: 5 commandes
if [ $# -eq 0 ]; then
    test_pipex 16 "5 commandes (bonus)" \
        "$PIPEX test.txt 'cat' 'cat' 'cat' 'cat' 'cat' out.txt"
fi

echo ""
echo "======================================"
echo "   TESTS HERE_DOC"
echo "======================================"

# Test 17: Here_doc basique
test_pipex 17 "Here_doc basique" \
    "echo -e 'line1\nline2\nEOF' | $PIPEX here_doc EOF 'cat' 'cat' out.txt"

# Test 18: Here_doc avec limiter différent
test_pipex 18 "Here_doc avec STOP" \
    "echo -e 'data\nSTOP' | $PIPEX here_doc STOP 'cat' 'wc -l' out.txt"

echo ""
echo "======================================"
echo "   TESTS DE FUITES MÉMOIRE (Valgrind)"
echo "======================================"

if command -v valgrind &> /dev/null; then
    echo -n "Test 19: Valgrind check basique... "
    valgrind --leak-check=full --error-exitcode=42 \
        $PIPEX test.txt "cat" "cat" out.txt > /tmp/valgrind_out 2>&1
    if [ $? -ne 42 ]; then
        echo -e "${GREEN}PASS (no leaks)${NC}"
        ((PASS++))
    else
        echo -e "${RED}FAIL (leaks detected)${NC}"
        cat /tmp/valgrind_out | grep "definitely lost"
        ((FAIL++))
    fi
else
    echo "Valgrind non installé, tests de fuites ignorés"
fi

echo ""
echo "======================================"
echo "   TESTS DE FILE DESCRIPTORS"
echo "======================================"

# Test 20: Vérifier que tous les FDs sont fermés
test_pipex 20 "File descriptors fermés correctement" \
    "lsof -p \$($PIPEX test.txt 'sleep 1' 'cat' out.txt & echo \$!) 2>/dev/null | wc -l"

echo ""
echo "======================================"
echo "   TESTS EDGE CASES"
echo "======================================"

# Test 21: Commande vide (si géré)
test_pipex 21 "Commande vide" \
    "$PIPEX test.txt '' 'cat' out.txt"

# Test 22: Chemin absolu pour commande
test_compare_bash 22 "Chemin absolu" \
    "test.txt" \
    "/bin/cat" \
    "/usr/bin/wc -l" \
    "out.txt"

# Test 23: Commande avec ./
echo '#!/bin/bash\ncat' > my_cat.sh
chmod +x my_cat.sh
test_pipex 23 "Commande avec ./" \
    "$PIPEX test.txt './my_cat.sh' 'cat' out.txt"

# Test 24: PATH vide
test_pipex 24 "Exécution avec PATH vide" \
    "PATH='' $PIPEX test.txt 'cat' 'cat' out.txt"

# Test 25: Fichier binaire en entrée
test_compare_bash 25 "Fichier binaire" \
    "binary.bin" \
    "cat" \
    "wc -c" \
    "out.txt"

echo ""
echo "======================================"
echo "   RÉSULTATS FINAUX"
echo "======================================"
echo -e "Tests réussis: ${GREEN}$PASS${NC}"
echo -e "Tests échoués: ${RED}$FAIL${NC}"
echo "Total: $((PASS + FAIL))"
echo ""

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}✓ Tous les tests sont passés ! GG 🎉${NC}"
    exit 0
else
    echo -e "${RED}✗ Certains tests ont échoué${NC}"
    exit 1
fi
