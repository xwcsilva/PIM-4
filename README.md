# PIM-4

Código fonte e arquivos acessórios para execução do projeto para o PIM-4 do curso Análise e Desenvovimento de Sistemas do 2º Semestre de 2022 da UNIP.

# Requisitos para compilação e execuçao:
- Instalar o Codeblocks: https://www.codeblocks.org/downloads/
- Instalar o GCC: https://gcc.gnu.org/install/binaries.html
- Abrir o Codeblocks e carregar o projeto, em seguida executar o programa via F9.

Na primeira execução, não há arquivo de configração de usuários, logo o sistema pedirá que seja fornecido um usuário e a respectiva senha, os dados são case sensitive e aceitam até 10 caracteres para o nome e senha, se precisar de tamanhos maiores, favor alterar o tamanho na struct usuario no aruivo tipos.h - as estrturas de armazenmanento dos dados de usuários e de pacientes estão neste arquivo tipos.h, se precisar alterar algo dos campos e seus tamanhos, o local é aqui. Lembre-se que se ajustar os tipos/tamanhos dos campos das structs, apagar os arquivos "usuarios", "pacientes" pois estes arquivos dependem dos tipos e tamanhos dos campos definidos no "tipos.h".

Após a definição do primeiro usuário, o sistema guarda ele no arquivo "usuarios" no diretório corrente e vai para o menu principal do programa, onde consta a opção de adição de mais usuários.

Nas próximas execuções do programa, ele solicita que seja informado um usário e a respectiva senha, se estes não concidirem com algum usuário do arquivo "usuarios", o programa informa isso e termina. 

Para o cadastro de pacientes, usar a opção correspondente "Adicione um paciente", onde serão requisitados os dados do paciente; as outras opções são auto-explicativas. Na opção "Gera arquivo com os dados para a Secretaria de Saude" é gerado um arquivo texto com nome "relatorio.txt" com o CEP e a idade do paciente, conforme o manual do PIM-4.

Ao término do programa, os arquivos "usuarios" e "pacientes" são atualizados, logo é fundamental que seja escolhida a opção "Fim" para que isso aconteça corretamente e os arquivos mantenham a consistÊncia com o que foi informado pelo usuário ao programa.

Se quiser reiniciar dos dados do pacientes, com o programa parado, basta apagar o arquivo correspondente no diretório: "pacientes". O mesmo se dá para o arquivo de usuários, apagar o arquivo "usuários".

Quaisquer dúvidas, favor abrir uma issue.
