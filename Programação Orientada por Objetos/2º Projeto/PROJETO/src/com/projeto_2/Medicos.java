package com.projeto_2;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Scanner;

public class Medicos implements Comparable<Medicos> {


    private ArrayList<Integer> Array_avaliacao;
    private int num_medico_unico;
    private int divisao;
    private int avaliacao_media;
    private int soma = 0;

    private Scanner scan = new Scanner( System.in );
    private String especialidade;

    private ArrayList<Calendar> consultas_dia = new ArrayList<>();

    public Medicos(int num_medico_unico, String especialidade) {
        this.especialidade = especialidade;
        this.num_medico_unico = num_medico_unico;
        avaliacao_media = 0;
        Array_avaliacao = new ArrayList<Integer>();
    }

    public int getAvaliacao_media( ) {
        return avaliacao_media;
    }

    public int getNum_medico_unico( ) {
        return num_medico_unico;
    }

    public String getEspecialidade( ) {
        return especialidade;
    }

    public void setAvaliacao(Integer avaliacao) {
        Array_avaliacao.add( avaliacao );
    }

    public ArrayList<Integer> getArray_avaliacao( ) {
        return Array_avaliacao;
    }


    public int media( ) {
        divisao = (Array_avaliacao.size());
        if (divisao == 0)
            return avaliacao_media = 0;

        else {
            soma = 0;
            for (Integer elemento : Array_avaliacao)
                soma = soma + elemento;
            avaliacao_media = (soma / divisao);

            return avaliacao_media;
        }
    }
    public int compareTo(Medicos medicos) {
        if (this.avaliacao_media > medicos.getAvaliacao_media( )) {
            return -1;
        }
        if (this.avaliacao_media < medicos.getAvaliacao_media( )) {
            return 1;
        }
        return 0;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        } else if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Medicos med = (Medicos) obj;
        return (num_medico_unico == med.getNum_medico_unico());
    }

    @Override
    public String toString( ) {
        return "\n - Numero unico -" + num_medico_unico +
                "\n - Especialidade - " + especialidade +
                "\n - Avaliação - " + media() + '\n' +
                " - Historico de avaliacoes " + getArray_avaliacao();
    }
}
