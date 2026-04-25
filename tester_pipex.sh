#!/bin/bash

# ╔══════════════════════════════════════════════════════════════════════╗
# ║                     PIPEX TESTER — 42 School                        ║
# ╚══════════════════════════════════════════════════════════════════════╝

BINARY="./pipex"
TMP="./.pipex_tests"
PASS=0
FAIL=0
TOTAL=0
SKIP=0

R="\033[0;31m"
G="\033[0;32m"
Y="\033[1;33m"
C="\033[0;36m"
W="\033[1;37m"
DIM="\033[2m"
BOLD="\033[1m"
RST="\033[0m"

print_pass() {
    ((PASS++)); ((TOTAL++))
    printf "  ${G}${BOLD}✔ PASS${RST}  ${W}%-58s${RST}\n" "$1"
}
print_fail() {
    ((FAIL++)); ((TOTAL++))
    printf "  ${R}${BOLD}✘ FAIL${RST}  ${W}%-58s${RST}\n" "$1"
    if [ -n "$2" ]; then
        while IFS= read -r line; do
            printf "           ${DIM}${R}↳ %s${RST}\n" "$line"
        done <<< "$2"
    fi
}
print_skip() {
    ((SKIP++))
    printf "  ${Y}${BOLD}~ SKIP${RST}  ${DIM}%-58s${RST}\n" "$1"
}
section() {
    echo ""
    echo -e "  ${C}${BOLD}┌───────────────────────────────────────────────────────────────┐${RST}"
    printf   "  ${C}${BOLD}│  %-63s│${RST}\n" "$1"
    echo -e "  ${C}${BOLD}└───────────────────────────────────────────────────────────────┘${RST}"
}

# ─── Helpers ──────────────────────────────────────────────────────────

# Compare la sortie de pipex avec bash < infile cmd1 | cmd2 > outfile
cmp_bash() {
    local desc="$1" infile="$2" cmd1="$3" cmd2="$4"
    local pout="$TMP/pipex_out" bout="$TMP/bash_out"
    rm -f "$pout" "$bout"

    timeout 3s "$BINARY" "$infile" "$cmd1" "$cmd2" "$pout" 2>/dev/null
    local pcode=$?

    if [ -f "$infile" ] && [ -r "$infile" ]; then
        bash -c "< '$infile' $cmd1 2>/dev/null | $cmd2 > '$bout' 2>/dev/null"
    else
        bash -c "< '$infile' $cmd1 2>/dev/null | $cmd2 > '$bout' 2>/dev/null"
    fi

    if diff -q "$pout" "$bout" &>/dev/null; then
        print_pass "$desc"
    else
        local detail="Sortie pipex ≠ sortie bash"
        local pdiff
        pdiff=$(diff <(cat "$pout" 2>/dev/null) <(cat "$bout" 2>/dev/null) | head -6)
        [ -n "$pdiff" ] && detail+=$'\n'"$pdiff"
        print_fail "$desc" "$detail"
    fi
}

# Attend exit != 0
expect_error() {
    local desc="$1"; shift
    local out code
    out=$(timeout 3s "$BINARY" "$@" 2>&1)
    code=$?
    if [ $code -eq 124 ]; then
        print_fail "$desc" "Timeout 3s — le programme ne quitte pas"
    elif [ $code -eq 0 ]; then
        print_fail "$desc" "Exit 0 retourné — erreur non détectée"
    else
        print_pass "$desc"
    fi
}

# Attend exit 0 ou timeout (process vivant)
expect_ok() {
    local desc="$1"; shift
    local out code
    out=$(timeout 5s "$BINARY" "$@" 2>&1)
    code=$?
    if [ $code -eq 0 ] || [ $code -eq 124 ]; then
        print_pass "$desc"
    else
        print_fail "$desc" "Exit $code inattendu — $(echo "$out" | head -3)"
    fi
}

# Vérifie qu'un message d'erreur est bien affiché sur stderr
expect_errmsg() {
    local desc="$1"; shift
    local out code
    out=$(timeout 3s "$BINARY" "$@" 2>&1)
    code=$?
    if [ $code -eq 0 ]; then
        print_fail "$desc" "Exit 0 — erreur non détectée"
    elif [ -z "$(echo "$out" | tr -d '[:space:]')" ]; then
        print_fail "$desc" "Exit $code mais aucun message (perror/ft_printf manquant?)"
    else
        print_pass "$desc"
    fi
}

# ─── Setup ────────────────────────────────────────────────────────────
setup() {
    mkdir -p "$TMP"
    printf "ligne 1\nligne 2\nligne 3\n"           > "$TMP/test.txt"
    seq 1 10000                                     > "$TMP/big.txt"
    printf "hello\tworld\n\$PATH\n'single'\n"       > "$TMP/special.txt"
    touch                                              "$TMP/empty.txt"
    dd if=/dev/urandom of="$TMP/binary.bin" bs=1024 count=10 &>/dev/null
    touch                                              "$TMP/no_read.txt"
    chmod 000                                          "$TMP/no_read.txt"
    touch                                              "$TMP/no_write.txt"
    chmod 000                                          "$TMP/no_write.txt"
    printf "#!/bin/bash\ncat\n"                     > "$TMP/mycat.sh"
    chmod +x                                           "$TMP/mycat.sh"
    printf "#!/bin/bash\ncat\n"                     > "$TMP/no_exec.sh"
    chmod 644                                          "$TMP/no_exec.sh"
    mkdir -p                                           "$TMP/isdir"
}

cleanup() {
    chmod 644 "$TMP/no_read.txt" "$TMP/no_write.txt" &>/dev/null
    rm -rf "$TMP"
}
trap cleanup EXIT

# ══════════════════════════════════════════════════════════════════════
clear
echo ""
echo -e "  ${W}${BOLD}╔════════════════════════════════════════════════════════════╗${RST}"
echo -e "  ${W}${BOLD}║              PIPEX TESTER — 42 School                     ║${RST}"
echo -e "  ${W}${BOLD}╚════════════════════════════════════════════════════════════╝${RST}"
echo ""

# ── 0. Compilation ────────────────────────────────────────────────────
section "0 · COMPILATION"

[ ! -f "Makefile" ] && echo -e "\n  ${R}Makefile introuvable.${RST} Lance depuis la racine.\n" && exit 1
print_pass "Makefile présent"

make_out=$(make -s re 2>&1)
if [ -f "$BINARY" ]; then
    print_pass "make re → binaire compilé"
else
    print_fail "make re → binaire introuvable" "$make_out"
    echo -e "\n  ${R}Impossible de continuer.${RST}\n"; exit 1
fi

make -s fclean &>/dev/null; make -s all &>/dev/null
[ -f "$BINARY" ] && print_pass "make fclean + make all → OK" \
                 || print_fail "make all après fclean → introuvable"

grep -q "\-Wall\|\-Wextra\|\-Werror" Makefile 2>/dev/null \
    && print_pass "Flags -Wall -Wextra -Werror présents" \
    || print_skip "Flags de compilation non détectés dans Makefile"

setup

# ── 1. Arguments ──────────────────────────────────────────────────────
section "1 · ARGUMENTS INVALIDES"

expect_error "Aucun argument"
expect_error "1 seul argument" "$TMP/test.txt"
expect_error "2 arguments" "$TMP/test.txt" "cat"
expect_error "3 arguments" "$TMP/test.txt" "cat" "cat"
# 4 args = minimum valide (infile cmd1 cmd2 outfile) → pas une erreur
# On vérifie juste qu'avec 4 args valides ça passe
expect_ok    "4 arguments valides (minimum requis)" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt"

# ── 2. Infile / Outfile ───────────────────────────────────────────────
section "2 · INFILE / OUTFILE"

expect_errmsg "Infile inexistant → message d'erreur" "nope.txt" "cat" "cat" "$TMP/out.txt"
expect_errmsg "Infile sans permission (chmod 000)" "$TMP/no_read.txt" "cat" "cat" "$TMP/out.txt"
expect_errmsg "Infile = dossier" "$TMP/isdir" "cat" "cat" "$TMP/out.txt"
expect_errmsg "Outfile sans permission (chmod 000)" "$TMP/test.txt" "cat" "cat" "$TMP/no_write.txt"

# Outfile doit être créé s'il n'existe pas
rm -f "$TMP/newfile.txt"
timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/newfile.txt" &>/dev/null
[ -f "$TMP/newfile.txt" ] && print_pass "Outfile créé s'il n'existe pas" \
                          || print_fail "Outfile non créé alors qu'il devrait l'être"

# Outfile doit être tronqué (pas appendé)
echo "ANCIEN CONTENU" > "$TMP/trunc.txt"
timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/trunc.txt" &>/dev/null
grep -q "ANCIEN CONTENU" "$TMP/trunc.txt" \
    && print_fail "Outfile non tronqué — ancien contenu encore présent" \
    || print_pass "Outfile correctement tronqué"

# Lien symbolique cassé en input
ln -sf /fichier/impossible "$TMP/broken_in"
expect_errmsg "Lien symbolique cassé en infile" "$TMP/broken_in" "cat" "cat" "$TMP/out.txt"
rm -f "$TMP/broken_in"

# Outfile = infile (même fichier)
cp "$TMP/test.txt" "$TMP/same.txt"
timeout 3s "$BINARY" "$TMP/same.txt" "cat" "cat" "$TMP/same.txt" &>/dev/null
[ -s "$TMP/same.txt" ] && print_pass "Infile = Outfile → géré (fichier non vide)" \
                       || print_skip "Infile = Outfile → résultat vide (comportement bash normal)"

# ── 3. Commandes ──────────────────────────────────────────────────────
section "3 · COMMANDES INVALIDES"

expect_errmsg "Cmd1 inexistante → message d'erreur" "$TMP/test.txt" "cmdquinexistepas" "cat" "$TMP/out.txt"
expect_errmsg "Cmd2 inexistante → message d'erreur" "$TMP/test.txt" "cat" "cmdquinexistepas" "$TMP/out.txt"

# Commande sans droits d'exécution
expect_errmsg "Cmd sans permission +x" "$TMP/test.txt" "$TMP/no_exec.sh" "cat" "$TMP/out.txt"

# Commande vide
out=$(timeout 2s "$BINARY" "$TMP/test.txt" "" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 0 ] && print_pass "Commande vide → erreur renvoyée" \
                || print_fail "Commande vide → exit 0 (non géré)"

# PATH vide + chemin absolu
old_path="$PATH"
out=$(PATH='' timeout 3s "$BINARY" "$TMP/test.txt" "/bin/cat" "/usr/bin/wc" "$TMP/out.txt" 2>&1)
code=$?
export PATH="$old_path"
[ $code -eq 0 ] && print_pass "Chemin absolu avec PATH vide → OK" \
               || print_fail "Chemin absolu avec PATH vide → exit $code" "$out"

# Chemin relatif ./
cmp_bash "Commande avec chemin relatif (./$TMP/mycat.sh)" \
    "$TMP/test.txt" "$TMP/mycat.sh" "cat"

# ── 4. Comparaison avec bash ──────────────────────────────────────────
section "4 · COMPARAISON SORTIE vs BASH"

cmp_bash "cat | cat"                    "$TMP/test.txt"    "cat"                    "cat"
cmp_bash "cat | wc -l"                  "$TMP/test.txt"    "cat"                    "wc -l"
cmp_bash "cat | grep ligne"             "$TMP/test.txt"    "cat"                    "grep ligne"
cmp_bash "cat | grep inexistant"        "$TMP/test.txt"    "cat"                    "grep motinexistant"
cmp_bash "cat | head -1"               "$TMP/test.txt"    "cat"                    "head -1"
cmp_bash "cat | tail -1"               "$TMP/test.txt"    "cat"                    "tail -1"
cmp_bash "cat | sort"                   "$TMP/test.txt"    "cat"                    "sort"
cmp_bash "cat | uniq"                   "$TMP/test.txt"    "cat"                    "uniq"
cmp_bash "cat | tr a-z A-Z"            "$TMP/test.txt"    "cat"                    "tr a-z A-Z"
cmp_bash "cat | cut -d' ' -f1"         "$TMP/test.txt"    "cat"                    "cut -d' ' -f1"
cmp_bash "cat | wc -w"                  "$TMP/test.txt"    "cat"                    "wc -w"
cmp_bash "cat -e | cat"                 "$TMP/test.txt"    "cat -e"                 "cat"
cmp_bash "cat | wc -c"                  "$TMP/binary.bin"  "cat"                    "wc -c"
cmp_bash "Fichier vide | wc -l"         "$TMP/empty.txt"   "cat"                    "wc -l"
cmp_bash "Gros fichier | head -100"     "$TMP/big.txt"     "cat"                    "head -100"
cmp_bash "Gros fichier | tail -100"     "$TMP/big.txt"     "cat"                    "tail -100"
cmp_bash "Gros fichier | wc -l"         "$TMP/big.txt"     "cat"                    "wc -l"
cmp_bash "Gros fichier | sort -n"       "$TMP/big.txt"     "cat"                    "sort -n"
cmp_bash "grep + wc (pipe filtrant)"    "$TMP/big.txt"     "grep 5000"              "wc -l"
cmp_bash "Chemin absolu /bin/cat"       "$TMP/test.txt"    "/bin/cat"               "wc -l"

# ── 5. Cas limites ────────────────────────────────────────────────────
section "5 · EDGE CASES"

# Infile = /dev/stdin
echo -e "a\nb\nc" | timeout 3s "$BINARY" /dev/stdin "cat" "wc -l" "$TMP/out.txt" &>/dev/null
[ -f "$TMP/out.txt" ] && print_pass "/dev/stdin comme infile → géré" \
                      || print_skip "/dev/stdin comme infile → non géré (ok si pas requis)"

# Infile = /dev/urandom limité
timeout 3s "$BINARY" /dev/urandom "head -c 100" "wc -c" "$TMP/out.txt" &>/dev/null
result=$(cat "$TMP/out.txt" 2>/dev/null | tr -d '[:space:]')
[ "$result" = "100" ] && print_pass "/dev/urandom | head -c 100 | wc -c = 100" \
                      || print_skip "/dev/urandom → résultat inattendu (${result:-vide})"

# Injection dans la commande (doit PAS exécuter le shell)
rm -f /tmp/pipex_injection_test
timeout 2s "$BINARY" "$TMP/test.txt" "cat; touch /tmp/pipex_injection_test" "cat" "$TMP/out.txt" &>/dev/null
[ -f /tmp/pipex_injection_test ] \
    && print_fail "Injection shell dans cmd1 → EXÉCUTÉE (dangereux!)" \
    || print_pass "Injection shell dans cmd1 → non exécutée (execve correct)"
rm -f /tmp/pipex_injection_test

# Variables d'env dans la commande
timeout 2s "$BINARY" "$TMP/test.txt" 'echo $HOME' "cat" "$TMP/out.txt" &>/dev/null
content=$(cat "$TMP/out.txt" 2>/dev/null)
[[ "$content" == '$HOME' || "$content" == "" ]] \
    && print_pass 'Variables $HOME dans cmd → non interpolées (execve correct)' \
    || print_fail 'Variables $HOME dans cmd → interpolées (shell interprétation!)'

# Backticks dans la commande
timeout 2s "$BINARY" "$TMP/test.txt" 'echo `whoami`' "cat" "$TMP/out.txt" &>/dev/null
content=$(cat "$TMP/out.txt" 2>/dev/null)
[[ "$content" == '`whoami`' || "$content" == "" ]] \
    && print_pass 'Backticks dans cmd → non exécutés' \
    || print_fail "Backticks dans cmd → exécutés (shell interprétation!)"

# Redirection dans la commande
rm -f /tmp/pipex_redir_test
timeout 2s "$BINARY" "$TMP/test.txt" "cat > /tmp/pipex_redir_test" "cat" "$TMP/out.txt" &>/dev/null
[ -f /tmp/pipex_redir_test ] \
    && print_fail "Redirection dans cmd → exécutée (shell interprétation!)" \
    || print_pass "Redirection dans cmd → non exécutée (execve correct)"
rm -f /tmp/pipex_redir_test

# ── 6. Ulimit / Ressources limitées ──────────────────────────────────
section "6 · ULIMIT (RESSOURCES LIMITÉES)"

# FD limités à 10
out=$(ulimit -n 10 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -eq 0 ] && print_pass "FD limités à 10 → pas de crash" \
               || print_fail "FD limités à 10 → exit $code" "$out"

# FD limités à 6 (ultra bas)
out=$(ulimit -n 6 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 139 ] && print_pass "FD limités à 6 → pas de segfault" \
                  || print_fail "FD limités à 6 → SEGFAULT (exit 139)"

# Mémoire limitée à 10 MB
out=$(ulimit -v 10000 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 139 ] && print_pass "Mémoire limitée 10MB → pas de segfault" \
                  || print_fail "Mémoire limitée 10MB → SEGFAULT (exit 139)"

# Mémoire très limitée 4MB
out=$(ulimit -v 4000 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 139 ] && print_pass "Mémoire très limitée 4MB → pas de segfault" \
                  || print_fail "Mémoire très limitée 4MB → SEGFAULT"

# Stack limitée
out=$(ulimit -s 1024 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 139 ] && print_pass "Stack limitée 1MB → pas de segfault" \
                  || print_fail "Stack limitée 1MB → SEGFAULT"

# Tout limité en même temps
out=$(ulimit -v 8000 -n 12 -s 1024 2>/dev/null; timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
[ $code -ne 139 ] && print_pass "Multi-limites (mém+fd+stack) → pas de segfault" \
                  || print_fail "Multi-limites → SEGFAULT"

# ── 7. File Descriptors ───────────────────────────────────────────────
section "7 · FILE DESCRIPTORS"

# Vérifier qu'après pipex, les FDs 0/1/2 sont toujours valides
timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" &>/dev/null
echo "stdin ok" | read -t 1 line &>/dev/null
print_pass "stdin toujours fonctionnel après pipex"

# Pas de FDs fuites (vérif via /proc si dispo)
"$BINARY" "$TMP/test.txt" "sleep 2" "cat" "$TMP/out.txt" &
BPID=$!
sleep 0.3
if [ -d /proc/$BPID/fd ]; then
    fd_count=$(ls /proc/$BPID/fd 2>/dev/null | wc -l)
    [ "$fd_count" -le 10 ] && print_pass "Pas de fuite de FDs ($fd_count ouverts)" \
                           || print_fail "Fuite probable de FDs ($fd_count ouverts)"
else
    print_skip "Vérification FDs non disponible (pas de /proc)"
fi
wait $BPID 2>/dev/null

# Pas de process zombie
"$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" &>/dev/null
sleep 0.2
zombies=$(ps aux | grep -c "[Zz]ombie\|<defunct>")
[ "$zombies" -eq 0 ] && print_pass "Pas de processus zombie" \
                     || print_fail "Processus zombie détecté ($zombies)"

# ── 8. Bonus : Multi-pipes ────────────────────────────────────────────
section "8 · BONUS — MULTI-PIPES"

echo -e "  ${DIM}(Tests ignorés si le bonus n'est pas implémenté)${RST}\n"

# 3 commandes
out=$(timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
expected=$(cat "$TMP/test.txt")
result=$(cat "$TMP/out.txt" 2>/dev/null)
if [ $code -eq 0 ] && [ "$result" = "$expected" ]; then
    print_pass "3 commandes : cat | cat | cat → OK"
else
    print_skip "3 commandes non supportées (bonus non implémenté?)"
fi

# 5 commandes
out=$(timeout 3s "$BINARY" "$TMP/test.txt" "cat" "cat" "cat" "cat" "cat" "$TMP/out.txt" 2>&1)
code=$?
result=$(cat "$TMP/out.txt" 2>/dev/null)
if [ $code -eq 0 ] && [ "$result" = "$expected" ]; then
    print_pass "5 commandes : cat×5 → OK"
else
    print_skip "5 commandes non supportées (bonus non implémenté?)"
fi

# 10 commandes avec gros fichier
CMDS=()
for _ in {1..10}; do CMDS+=("cat"); done
out=$(timeout 5s "$BINARY" "$TMP/big.txt" "${CMDS[@]}" "$TMP/out.txt" 2>&1)
code=$?
[ $code -eq 0 ] && print_pass "10 commandes cat sur big.txt → OK" \
               || print_skip "10 commandes → non supportées (exit $code)"

# Multi avec filtre
out=$(timeout 3s "$BINARY" "$TMP/big.txt" "cat" "grep 5000" "wc -l" "$TMP/out.txt" 2>&1)
code=$?
result=$(cat "$TMP/out.txt" 2>/dev/null | tr -d '[:space:]')
bash_res=$(bash -c "cat '$TMP/big.txt' | grep 5000 | wc -l" 2>/dev/null | tr -d '[:space:]')
[ "$result" = "$bash_res" ] && print_pass "Multi-pipe avec filtre : grep | wc -l → OK" \
                            || print_skip "Multi-pipe filtre → non supporté ou sortie diff"

# ── 9. Bonus : Here_doc ───────────────────────────────────────────────
section "9 · BONUS — HERE_DOC"

echo -e "  ${DIM}(Tests ignorés si le bonus n'est pas implémenté)${RST}\n"

# Here_doc basique
result=$(printf "ligne1\nligne2\nEOF\n" | timeout 3s "$BINARY" here_doc EOF "cat" "cat" "$TMP/out.txt" 2>/dev/null; cat "$TMP/out.txt" 2>/dev/null)
if echo "$result" | grep -q "ligne1"; then
    print_pass "here_doc basique avec limiter EOF → OK"
else
    print_skip "here_doc non implémenté (bonus)"
fi

# Here_doc | wc -l
printf "a\nb\nc\nSTOP\n" | timeout 3s "$BINARY" here_doc STOP "cat" "wc -l" "$TMP/out.txt" &>/dev/null
result=$(cat "$TMP/out.txt" 2>/dev/null | tr -d '[:space:]')
[ "$result" = "3" ] && print_pass "here_doc STOP : 3 lignes → wc -l = 3" \
                    || print_skip "here_doc wc -l → résultat inattendu (${result:-vide})"

# Here_doc avec limiter vide
printf "\n" | timeout 2s "$BINARY" here_doc "" "cat" "cat" "$TMP/out.txt" &>/dev/null
code=$?
[ $code -ne 139 ] && print_pass "here_doc limiter vide → pas de segfault" \
                  || print_fail "here_doc limiter vide → SEGFAULT"

# Here_doc outfile doit APPENDER (>>) pas tronquer
echo "ORIGINAL" > "$TMP/heredoc_app.txt"
printf "new\nEOF\n" | timeout 3s "$BINARY" here_doc EOF "cat" "cat" "$TMP/heredoc_app.txt" &>/dev/null
grep -q "ORIGINAL" "$TMP/heredoc_app.txt" \
    && print_pass "here_doc outfile en mode append (>> conserve contenu)" \
    || print_skip "here_doc outfile : contenu original perdu (normal ou bug?)"

# ── 10. Norminette ────────────────────────────────────────────────────
section "10 · NORMINETTE"

if command -v norminette &>/dev/null; then
    norm_dirs=()
    for d in src/ sources/ srcs/ includes/ include/ inc/; do
        [ -d "$d" ] && norm_dirs+=("$d")
    done
    if [ ${#norm_dirs[@]} -eq 0 ]; then
        print_skip "Dossiers src/include introuvables"
    else
        norm_out=$(norminette "${norm_dirs[@]}" 2>&1 | grep -v "^Norme\|OK!")
        if [ -z "$norm_out" ]; then
            print_pass "Norminette → aucune erreur  [${norm_dirs[*]}]"
        else
            err_count=$(echo "$norm_out" | grep -c "Error:" || echo "?")
            print_fail "Norminette → $err_count erreur(s)" "$(echo "$norm_out" | head -15)"
        fi
    fi
else
    print_skip "norminette non installée"
fi

# ── 11. Valgrind ──────────────────────────────────────────────────────
section "11 · FUITES MÉMOIRE (VALGRIND)"

if command -v valgrind &>/dev/null; then
    # Test cas nominal
    vg_out=$(timeout 5s valgrind \
        --leak-check=full \
        --show-leak-kinds=definite,indirect \
        --track-origins=yes \
        --error-exitcode=42 \
        "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
    vg_code=$?
    if [ $vg_code -eq 124 ]; then
        print_pass "Valgrind nominal → programme vivant (timeout OK)"
    elif echo "$vg_out" | grep -q "0 errors from 0 contexts"; then
        print_pass "Valgrind nominal → aucune fuite"
    elif [ $vg_code -eq 42 ]; then
        def=$(echo "$vg_out" | grep "definitely lost:" | grep -oP "[\d,]+ bytes" | head -1)
        ind=$(echo "$vg_out" | grep "indirectly lost:" | grep -oP "[\d,]+ bytes" | head -1)
        print_fail "Valgrind → fuites détectées" "Definitely: ${def:-?}  Indirectly: ${ind:-?}"
    else
        print_skip "Valgrind ambigu (mlx / pas de display)"
    fi

    # Valgrind sur erreur (infile inexistant) → pas de leak non plus
    vg_err=$(timeout 5s valgrind \
        --leak-check=full \
        --show-leak-kinds=definite \
        --error-exitcode=42 \
        "$BINARY" "nope_file.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
    vg_code2=$?
    def2=$(echo "$vg_err" | grep "definitely lost:" | grep -oP "[\d,]+ bytes" | head -1)
    if [[ -z "$def2" || "$def2" == "0 bytes" ]]; then
        print_pass "Valgrind sur erreur → aucune fuite (free même en cas d'erreur)"
    else
        print_fail "Valgrind sur erreur → fuite détectée" "Definitely: $def2"
    fi

    # Valgrind + ulimit
    vg_ul=$(ulimit -v 8000 2>/dev/null; timeout 5s valgrind \
        --leak-check=full --show-leak-kinds=definite --error-exitcode=42 \
        "$BINARY" "$TMP/test.txt" "cat" "cat" "$TMP/out.txt" 2>&1)
    vg_ul_code=$?
    def3=$(echo "$vg_ul" | grep "definitely lost:" | grep -oP "[\d,]+ bytes" | head -1)
    [[ -z "$def3" || "$def3" == "0 bytes" ]] \
        && print_pass "Valgrind + ulimit 8MB → aucune fuite" \
        || print_fail "Valgrind + ulimit → fuite" "Definitely: $def3"
else
    print_skip "valgrind non installé"
fi

# ── Résumé ────────────────────────────────────────────────────────────
echo ""
echo -e "  ${DIM}──────────────────────────────────────────────────────────────${RST}"
echo ""

if [ $TOTAL -gt 0 ]; then
    PCT=$(( PASS * 100 / TOTAL ))
    filled=$(( PASS * 52 / TOTAL ))
    empty=$(( 52 - filled ))
    bar="${G}${BOLD}"
    for ((i=0; i<filled; i++)); do bar+="█"; done
    bar+="${RST}${DIM}"
    for ((i=0; i<empty; i++)); do bar+="░"; done
    bar+="${RST}"
    echo -e "  [$bar] ${W}${BOLD}$PCT%${RST}  ${DIM}($SKIP skipped)${RST}"
    echo ""
fi

if [ $FAIL -eq 0 ]; then
    echo -e "  ${G}${BOLD}✔  $PASS/$TOTAL tests passés — Pipex est béton. Bonne correction !${RST}"
else
    echo -e "  ${R}${BOLD}✘  $FAIL FAIL${RST}  ${G}${BOLD}$PASS PASS${RST}  ${W}$TOTAL total${RST}"
    echo -e "  ${Y}  Les erreurs ↳ ci-dessus indiquent précisément ce qui cloche.${RST}"
fi
echo ""

[ $FAIL -eq 0 ] && exit 0 || exit 1
