cmake_minimum_required(VERSION 3.27)
project(tp)

set(CMAKE_CXX_STANDARD 17)

add_executable(tp main.cpp
        Solo/Solo.cpp
        Solo/Solo.h
        Jardim/Jardim.cpp
        Jardim/Jardim.h
        Simulador/Simulador.cpp
        Simulador/Simulador.h
        Jardineiro/Jardineiro.cpp
        Jardineiro/Jardineiro.h
        Settings.h
        Plantas/Planta.cpp
        Plantas/Planta.h
        Plantas/tipos/Cacto/Cacto.cpp
        Plantas/tipos/Cacto/Cacto.h
        Plantas/tipos/ErvaDaninha/ErvaDaninha.cpp
        Plantas/tipos/ErvaDaninha/ErvaDaninha.h
        Plantas/tipos/Roseira/Roseira.cpp
        Plantas/tipos/Roseira/Roseira.h
        Plantas/tipos/PlantaExotica/PlantaExotica.cpp
        Plantas/tipos/PlantaExotica/PlantaExotica.h
        Ferramentas/Ferramenta.cpp
        Ferramentas/Ferramenta.h
        Ferramentas/tipos/Regador/Regador.cpp
        Ferramentas/tipos/Regador/Regador.h
        Ferramentas/tipos/Adubo/Adubo.cpp
        Ferramentas/tipos/Adubo/Adubo.h
        Ferramentas/tipos/Tesoura/Tesoura.cpp
        Ferramentas/tipos/Tesoura/Tesoura.h
        Ferramentas/tipos/FerramentaZ/FerramentaZ.cpp
        Ferramentas/tipos/FerramentaZ/FerramentaZ.h)
