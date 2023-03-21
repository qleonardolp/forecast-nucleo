# Forecast Nucleo Framework - Legged Robotics Group (LegRo)

Este repositório é dedicado ao desenvolvimento do software embarcado na placa STM32 NUCLEO-F446RE com a bancada de testes IC2D usando a interface gráfica ForceCAST Studio. Inicialmente esse repositório se destina a ser o ambiente de desenvolvimento dedicado à IC2D, sem interação com os repositórios originais do **_AltairLab_**, apesar de herdar o histórico git original. Para acessar o repositório orginal, [clique aqui](https://gitlab.com/altairLab/elasticteam/ForecastNucleoFramework-test/-/tree/NEXT/).

Outro objetivo desse repositório é servir de base para o versionamento do código fonte, enquanto utilizamos uma imagem Docker para facilitar o uso para diversos usuários. É recomendada experiência prévia mínina com _git_ e _linux_ para configuração desse ambiente de desenvolvimento.

## Configuração

1. Em sua máquina é necessário instalar o _git_ e, recomendado, o editor [Visual Studio Code](https://code.visualstudio.com/):

    ```bash
    sudo apt install git 
    sudo snap install code --classic
    ```

2. Instale o Docker em seu computador seguindo as instruções desse [repositório](https://github.com/lomcin/linux-stuffs#docker);

3. Gere a imagem e inicialize o _container_ 'nucleo-legged' segundo instruções desse [repositório](https://github.com/lomcin/legged_ws).


## Observações

A configuração deste repositório git, assim como a adoção da imagem docker, auxilia o desenvolvimento do software automatizando algumas configurações prévias e evitando erros provenientes de instalações locais (em cada computador). Aqui não é necessário resovler a instalação do [PlatformIO](https://docs.platformio.org/en/latest/what-is-platformio.html), muito menos a versão compatível do Python (3.6+ até 3.9!). Isso já está configurado na imagem docker. Quanto configuração original do repositório, tal como descrita [aqui](https://gitlab.com/altairLab/elasticteam/ForecastNucleoFramework-test/-/tree/NEXT/#get-the-firmware), também já está resolvida nesse novo repositório.

A única diferença é a necessidade de utilzarmos o PlatformIO pela linha de comando (CLI), já que não será feito uso da extensão no VS Code. A seguir estão as instruções para realizar compilação e envio para placa com o PlatformIO.

## Compilação e Envio: PlatformIO CLI

WIP...