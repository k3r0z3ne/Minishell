#!/bin/bash

# Couleurs pour les messages
green="\033[0;32m"
red="\033[0;31m"
reset="\033[0m"

echo "Running tests to compare echo and ./my_echo..."

# Dossier temporaire pour les fichiers de test
temp_dir=$(mktemp -d)

echo_file="$temp_dir/echo_output.txt"
my_echo_file="$temp_dir/my_echo_output.txt"
append_file="$temp_dir/append.txt"

# Fonction pour exécuter un test
test_case() {
    local description="$1"
    local command="$2"

    # Exécution de echo
    bash -c "$command" > "$echo_file" 2>/dev/null

    # Exécution de ./my_echo
    bash -c "${command/echo/./my_echo}" > "$my_echo_file" 2>/dev/null

    # Comparaison des résultats
    if diff "$echo_file" "$my_echo_file" > /dev/null; then
        echo -e "$green[OK]$reset $description"
    else
        echo -e "$red[KO]$reset $description"
        echo "  Command: $command"
		# Afficher le test en cours
    	echo "Running test: $command"
        echo "  Diff:" && diff "$echo_file" "$my_echo_file"
		echo "  Running Valgrind for ./my_echo..." && valgrind --leak-check=full --track-origins=yes -q ./my_echo ${command#echo}
    fi
}

# Liste des tests
test_case "Commande sans argument" "echo"
test_case "Texte simple" "echo \"Hello, World!\""
test_case "Flag -n seul" "echo -n"
test_case "Flag -n avec texte" "echo -n \"No newline here\""
test_case "Flag -n avec espaces" "echo -n \"Line without newline \""
test_case "Plusieurs flags -n" "echo -n -n \"Testing multiple flags\""
test_case "Argument ressemblant à un flag" "echo -n-like-text"
test_case "Combinaison d'arguments" "echo \"Hello,\" -n \"world!\""
test_case "Caractères spéciaux" "echo \"Special characters: !@#$%^&*()\""
test_case "Retour chariot dans le texte" "echo -n \"Line1\\nLine2\""
test_case "Variable vide" "VAR=\"\"; echo $VAR"
test_case "Variable avec texte" "VAR=\"Hello, variable!\"; echo $VAR"
test_case "Texte avec caractères Unicode" "echo \"Éléphant 🐘 et caractères 漢字\""
test_case "Texte avec guillemets échappés" "echo \"He said \\\"Hello\\\"\""
test_case "Flag -n avec texte contenant retour chariot" "echo -n \"Line1\\nLine2\""
test_case "Flag -n avec texte vide" "echo -n \"\""
test_case "Combinaison complexe avec variables" "VAR1=\"abc\"; VAR2=\"def\"; echo \"Start $VAR1 middle $VAR2 end\""
test_case "Argument contenant espaces multiples" "echo \"Word1   Word2\""
test_case "Texte très long" "echo \"$(printf 'a%.0s' {1..10000})\""
test_case "Sortie redirigée avec ajout (>>)" "echo \"Append test\" >> $temp_dir/append_test; cat $temp_dir/append_test"
test_case "Chevauchement d'options et texte" "echo -n\"text\""
test_case "Commande dans une sous-shell" "(echo \"Subshell test\")"


# Redirection dans des fichiers
test_case "Redirection de sortie" "echo \"To file\" > $temp_dir/test_file"

# Nettoyage
echo "Cleaning up temporary files..."
rm -rf "$temp_dir"

echo "Tests completed."
