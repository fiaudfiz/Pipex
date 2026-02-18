#!/bin/bash

echo "======================================"
echo "   TESTS ULIMIT (Ressources limitées)"
echo "======================================"
echo ""

# Créer un fichier de test
echo -e "ligne 1\nligne 2\nligne 3" > /tmp/test_ulimit.txt

# 1. LIMITE DE MÉMOIRE (heap réduite)
echo "Test 1: Mémoire limitée (10 MB)"
(ulimit -v 10000; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 2. MÉMOIRE TRÈS LIMITÉE (4 MB) - Devrait échouer gracieusement
echo "Test 2: Mémoire TRÈS limitée (4 MB)"
(ulimit -v 4000; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 3. LIMITE DE PROCESSUS (fork limité)
echo "Test 3: Nombre de processus limité"
(ulimit -u 10; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 4. LIMITE DE FILE DESCRIPTORS
echo "Test 4: File descriptors limités (10)"
(ulimit -n 10; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 5. LIMITE DE FILE DESCRIPTORS ULTRA BASSE (6)
echo "Test 5: File descriptors ULTRA limités (6)"
(ulimit -n 6; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 6. LIMITE DE STACK SIZE
echo "Test 6: Stack limitée (1 MB)"
(ulimit -s 1024; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 7. COMBINAISON : Tout limité en même temps
echo "Test 7: TOUT limité (hardcore)"
(ulimit -v 8000 -u 15 -n 12 -s 1024; ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 8. Test avec MULTI-PIPES et limites
echo "Test 8: Multi-pipes (5 cmds) avec mémoire limitée"
(ulimit -v 15000; ./pipex /tmp/test_ulimit.txt "cat" "cat" "cat" "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 9. HERE_DOC avec limites
echo "Test 9: Here_doc avec mémoire limitée"
(ulimit -v 8000; echo -e "line1\nEOF" | ./pipex here_doc EOF "cat" "cat" /tmp/out.txt 2>&1)
echo "Exit code: $?"
echo ""

# 10. Test Valgrind + ulimit (vérifier qu'il n'y a pas de leak même avec erreurs)
echo "Test 10: Valgrind + ulimit (vérif leaks sur erreur)"
if command -v valgrind &> /dev/null; then
    (ulimit -v 8000; valgrind --leak-check=full --error-exitcode=42 \
        ./pipex /tmp/test_ulimit.txt "cat" "cat" /tmp/out.txt 2>&1 | grep -E "lost|ERROR")
else
    echo "Valgrind non installé"
fi
echo ""

echo "======================================"
echo "   VÉRIFICATION DES LEAKS"
echo "======================================"

# 11. Vérifier qu'il n'y a pas de leak quand malloc échoue
echo "Test 11: Pas de leak quand malloc échoue"
valgrind --leak-check=full --show-leak-kinds=all \
    bash -c "(ulimit -v 5000; ./pipex /tmp/test_ulimit.txt 'cat' 'cat' /tmp/out.txt)" 2>&1 | \
    grep -A5 "HEAP SUMMARY"
echo ""

echo "======================================"
echo "   TESTS TERMINÉS"
echo "======================================"
echo ""
echo "⚠️  CE QUI EST ATTENDU :"
echo "- Ton programme ne doit PAS crash (pas de segfault)"
echo "- Il doit retourner un exit code non-0 en cas d'erreur"
echo "- Il doit libérer TOUTE la mémoire même en cas d'échec"
echo "- Les messages d'erreur doivent être clairs (perror)"
echo ""
