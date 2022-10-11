# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLD="\033[1m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell
##ya peut etre un truc avec read pour les ';'

pipe=/tmp/testpipe
trap "rm -f $pipe" EXIT
if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

function exec_test()
{
	rm -f msh_log
	# execute commands, separated by ';' in minishell, using nfifo
	./minishell <$pipe >msh_log 2>&- &
	mshpid=$!
	IFS=';' read -ra CMND <<< "$@"
	for command in "${CMND[@]}"; do
		echo $command > $pipe
	done

	echo 'exit' > $pipe 
	sleep 0.03
	wait $!
	ES_1=$?
	TEST1=$(cat msh_log)

	rm -f msh_log
	#TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	#ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLD$GREEN%s$RESET" "✓ "
	else
		printf " $BOLD$RED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLD$RED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLD$GREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.01
}

#Wut?
exec_test "rien"
#exec_test "\ls"
exec_test "\$FALSE"
exec_test ' "" | "" '
exec_test '>>truc2'
exec_test "echo \$USER \"\$USER\" '\$USER'"
exec_test 'export LOL="         truc machin     " ; cat $LOL'

#Exit builtins
exec_test "exit 42"
exec_test "exit 0"
exec_test "exit truc"
exec_test "exit 42 56"
exec_test "exit"
exec_test "exit             "
exec_test "exit -1"
exec_test "exit 255"
exec_test "exit 256"
exec_test "exit 2147483647"
exec_test "exit 2147483648"
exec_test "exit 9223372036854775806"
exec_test "exit 9223372036854775807"
exec_test "exit 9223372036854775808"
exec_test "exit 9223372036854775818"
exec_test "exit 922337203685477580866"
exec_test "exit -9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit -9223372036854775809"
exec_test "exit -n"

exec_test "echo"
exec_test "echo "
exec_test "echo \$LESS"
exec_test "echo truc machin"
exec_test "echo truc        machin"
exec_test "echo \$?"
exec_test "echo -n truc"

exec_test "pwd"
exec_test "pwd truc"
exec_test "pwd > testpwd ; cat testpwd"
exec_test "pwd > testpwd"

exec_test "pwd ; cd ; pwd"
exec_test "pwd ; cd .. ; pwd"
exec_test "pwd ; cd false"
exec_test "pwd ; cd false ; pwd"

#exec_test "env"
exec_test "env truc"
exec_test "env -n truc"
exec_test "env truc machin"
exec_test "cd oui non"

exec_test "export TRUC=machin ; echo \$TRUC"
exec_test "export TRUC=machin  CHOSE=chouette ; echo \$TRUC ; echo \$CHOSE"

exec_test "export TRUC=machin ; echo \$TRUC ; unset TRUC ; echo \$TRUC"
exec_test "unset RIEN"

exec_test "cat test_cases.c"
exec_test "cat <test_cases.c"
exec_test "wc test_cases.c"

exec_test "cat <test_cases.c | wc"
exec_test "cat <test_cases.c >out1 ; <out1 wc "

exec_test "truc ; echo $?"
exec_test "/truc ; echo $?"
exec_test "touch test2 ; chmod 000 test2 ; cat test2 ; echo \$?"

exec_test "echo \"coucou a va?\" \"pas mal et toi?\""

#expnd tests
exec_test "echo $ "
exec_test "echo $"
exec_test "echo $\"rfrgrg\""
exec_test "echo $'rfrgrg'"
exec_test 'echo $rfrgrg'
exec_test "echo 'l"

#syntax error tests
exec_test "wc <"
exec_test "wc >"
exec_test "wc |"
exec_test "wc | |"
exec_test "wc |||"

exec_test "ls <non | wc"

rm -rf minishell out1 test2 testpwd truc2
#rm lol ls test