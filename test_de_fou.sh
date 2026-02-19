#!/bin/bash

# Tests BATARDS que même les correcteurs ne font pas 😈

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "======================================"
echo "   TESTS DE BATARD NIVEAU 9000 😈"
echo "======================================"
echo ""

PIPEX="./pipex"

# =====================================================
echo "🔥 TEST 1: Fichier avec des espaces et caractères spéciaux dans le nom"
touch "mon fichier avec espaces.txt"
echo "test" > "mon fichier avec espaces.txt"
$PIPEX "mon fichier avec espaces.txt" "cat" "wc -l" out.txt 2>&1
echo "Exit: $?"
rm -f "mon fichier avec espaces.txt"
echo ""

# =====================================================
echo "🔥 TEST 2: Commande avec 1000 caractères"
LONG_CMD=$(printf 'a%.0s' {1..1000})
$PIPEX test.txt "$LONG_CMD" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 3: Argument vide vs espace"
echo "test" > test.txt
$PIPEX "test.txt" "" "cat" out.txt 2>&1
echo "Exit code commande vide: $?"
$PIPEX "test.txt" " " "cat" out.txt 2>&1
echo "Exit code espace: $?"
$PIPEX "test.txt" "    " "cat" out.txt 2>&1
echo "Exit code multiples espaces: $?"
echo ""

# =====================================================
echo "🔥 TEST 4: PATH avec des paths bidons"
export PATH="/fake/path:/another/fake:/usr/bin"
$PIPEX test.txt "cat" "wc -l" out.txt 2>&1
echo "Exit: $?"
export PATH="/usr/bin:/bin"
echo ""

# =====================================================
echo "🔥 TEST 5: Commande qui existe MAIS sans droits d'exécution"
echo '#!/bin/bash\necho "hello"' > ./mycmd
chmod 644 ./mycmd  # Pas de +x
$PIPEX test.txt "./mycmd" "cat" out.txt 2>&1
echo "Exit: $?"
rm -f ./mycmd
echo ""

# =====================================================
echo "🔥 TEST 6: Fichier qui est un dossier"
mkdir -p fake_file
$PIPEX fake_file "cat" "wc -l" out.txt 2>&1
echo "Exit: $?"
rmdir fake_file
echo ""

# =====================================================
echo "🔥 TEST 7: Outfile qui est un dossier"
mkdir -p fake_out
$PIPEX test.txt "cat" "wc -l" fake_out 2>&1
echo "Exit: $?"
rmdir fake_out
echo ""

# =====================================================
echo "🔥 TEST 8: Lien symbolique cassé en input"
ln -s /fichier/qui/existe/pas broken_link
$PIPEX broken_link "cat" "wc -l" out.txt 2>&1
echo "Exit: $?"
rm -f broken_link
echo ""

# =====================================================
echo "🔥 TEST 9: Lien symbolique cassé en output"
ln -s /path/impossible/outfile broken_out
$PIPEX test.txt "cat" "wc -l" broken_out 2>&1
echo "Exit: $?"
rm -f broken_out
echo ""

# =====================================================
echo "🔥 TEST 10: Fichier avec des newlines dans le nom (si ton shell le permet)"
touch $'file\nwith\nnewlines.txt' 2>/dev/null
if [ -f $'file\nwith\nnewlines.txt' ]; then
    echo "test" > $'file\nwith\nnewlines.txt'
    $PIPEX $'file\nwith\nnewlines.txt' "cat" "wc -l" out.txt 2>&1
    echo "Exit: $?"
    rm -f $'file\nwith\nnewlines.txt'
else
    echo "Système ne supporte pas les newlines dans les noms"
fi
echo ""

# =====================================================
echo "🔥 TEST 11: Commande avec NULL byte (si possible)"
$PIPEX test.txt $'cat\x00hidden' "wc -l" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 12: FIFO (named pipe) en input"
mkfifo my_fifo 2>/dev/null
if [ -p my_fifo ]; then
    echo "test data" > my_fifo &
    timeout 2 $PIPEX my_fifo "cat" "wc -l" out.txt 2>&1
    echo "Exit: $?"
    rm -f my_fifo
else
    echo "mkfifo pas supporté"
fi
echo ""

# =====================================================
echo "🔥 TEST 13: /proc/self/fd/0 comme infile (stdin récursif)"
$PIPEX /proc/self/fd/0 "cat" "wc -l" out.txt 2>&1 < test.txt
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 14: Outfile = infile (même fichier)"
cp test.txt test_backup.txt
$PIPEX test_backup.txt "cat" "cat" test_backup.txt 2>&1
echo "Exit: $?"
cat test_backup.txt
rm -f test_backup.txt
echo ""

# =====================================================
echo "🔥 TEST 15: Commande = script shell qui fork bomb (non exécuté)"
echo '#!/bin/bash\n:(){ :|:& };:' > forkbomb.sh
chmod +x forkbomb.sh
# On teste juste que pipex peut le détecter, PAS l'exécuter
echo "(Test annulé pour sécurité)"
rm -f forkbomb.sh
echo ""

# =====================================================
echo "🔥 TEST 16: 100 pipes (si bonus activé)"
CMDS=""
for i in {1..100}; do
    CMDS="$CMDS \"cat\""
done
eval timeout 5 $PIPEX test.txt $CMDS out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 17: Commande avec injection de path (tentative)"
$PIPEX test.txt "cat; rm -rf /" "wc -l" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 18: Variables d'environnement dans la commande"
$PIPEX test.txt 'echo $HOME' "cat" out.txt 2>&1
echo "Exit: $?"
cat out.txt
echo ""

# =====================================================
echo "🔥 TEST 19: Backticks dans la commande"
$PIPEX test.txt 'echo \`whoami\`' "cat" out.txt 2>&1
echo "Exit: $?"
cat out.txt
echo ""

# =====================================================
echo "🔥 TEST 20: Redirection dans l'argument"
$PIPEX test.txt "cat > /tmp/hack.txt" "cat" out.txt 2>&1
echo "Exit: $?"
ls -la /tmp/hack.txt 2>&1
echo ""

# =====================================================
echo "🔥 TEST 21: Pipe dans l'argument"
$PIPEX test.txt "cat | grep test" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 22: Argc = 4 exactement (minimum)"
$PIPEX test.txt "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 23: Argc = 3"
$PIPEX test.txt "cat" 2>&1
echo "Exit: $?"
echo ""

# =====================================================
echo "🔥 TEST 24: Argc = 2"
$PIPEX test.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================================
echo "🔥 TEST 25: here_doc avec limiter qui contient des espaces"
echo -e "line1\nmy limiter\n" | $PIPEX here_doc "my limiter" "cat" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================================
echo "🔥 TEST 26: here_doc avec limiter vide"
echo -e "\n" | $PIPEX here_doc "" "cat" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================================
echo "🔥 TEST 27: Commande avec 50 arguments"
ARGS=""
for i in {1..50}; do
    ARGS="$ARGS -$i"
done
$PIPEX test.txt "ls $ARGS" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================================
echo "🔥 TEST 28: Infile = /dev/urandom (données infinies)"
timeout 1 $PIPEX /dev/urandom "head -c 100" "wc -c" out.txt 2>&1
echo "Exit: $?"
cat out.txt
echo ""

# =====================================================================
echo "🔥 TEST 29: Outfile sur filesystem plein (simulation impossible sans root)"
echo "Test ignoré (nécessite root)"
echo ""

# =====================================================================
echo "🔥 TEST 30: Kill -9 pendant l'exécution"
$PIPEX test.txt "sleep 10" "cat" out.txt &
PID=$!
sleep 0.5
kill -9 $PID 2>/dev/null
wait $PID 2>/dev/null
echo "Killed: Exit = $?"
# Vérifier qu'il n'y a pas de zombies
ps aux | grep -E "pipex|defunct" | grep -v grep
echo ""

# =====================================================================
echo "🔥 TEST 31: Même commande 10 fois"
$PIPEX test.txt "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" out.txt 2>&1
echo "Exit: $?"
echo ""

# =====================================================================
echo "🔥 TEST 32: Commande qui écrit sur stderr uniquement"
$PIPEX test.txt "ls /root 2>&1" "cat" out.txt 2>&1
echo "Exit: $?"
cat out.txt
echo ""

# =====================================================================
echo "🔥 TEST 33: Fichier en lecture seule (immutable)"
touch readonly.txt
chmod 444 readonly.txt
$PIPEX readonly.txt "cat" "wc -l" out.txt 2>&1
echo "Exit: $?"
rm -f readonly.txt
echo ""

# =====================================================================
echo "🔥 TEST 34: PATH = vide complètement"
export PATH=""
$PIPEX test.txt "/bin/cat" "/usr/bin/wc -l" out.txt 2>&1
echo "Exit: $?"
export PATH="/usr/bin:/bin"
echo ""

# =====================================================================
echo "🔥 TEST 35: Commande = chemin relatif complexe"
mkdir -p a/b/c
echo '#!/bin/bash\ncat' > a/b/c/mycat
chmod +x a/b/c/mycat
$PIPEX test.txt "./a/b/c/mycat" "cat" out.txt 2>&1
echo "Exit: $?"
rm -rf a
echo ""

echo "======================================"
echo "   FIN DES TESTS BATARDS"
echo "======================================"
echo ""
echo "⚠️  Si ton pipex a survécu à tout ça..."
echo "🏆 TU ES UN DIEU DU CODE ! 👑"

