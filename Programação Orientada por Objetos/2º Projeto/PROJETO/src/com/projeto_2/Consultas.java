package com.projeto_2;

import com.projeto_2.Medicos;
import com.projeto_2.Utentes;

import java.util.Calendar;
import java.util.Random;

public class Consultas {

    private static double Valor_a_pagar; // Static para encontrar a variavel local
    private Medicos medico;
    private Utentes utente;
    private int idade; // variavel para a idade

    private double valorExame = 80; // constante para o valor do exame
    private double valorConsulta = 100; // constante para o valor da consulta
    private boolean seg_med; // variavel boleana para verificar se tem seguro medico
    private boolean faz_exame; // variavel para verificar se fez exame

    private Calendar data_consulta = Calendar.getInstance();
    private Calendar data_exame = Calendar.getInstance();
    private Calendar data_consulta_resultados = Calendar.getInstance();
    private Calendar data_pagamento = Calendar.getInstance();

    /*
    Construtor para a classe consultas
     */
    public Consultas(Medicos medico, Utentes utente, int dia_pretendidio) {

        Valor_a_pagar = 0;

        data_consulta.set( Calendar.DAY_OF_MONTH, dia_pretendidio );

        this.medico = medico;
        this.utente = utente;
        this.idade = utente.getIdade();
        this.seg_med = utente.getSeguro();

        Exames();
        pagamento();
    }

/*
getter para retornar o valor a pagar
 */

    public static double getValor_a_pagar( ) {
        return Valor_a_pagar;
    }

    /*
    Metodo que faz que com o medico mande fazer exame ou nao
     */
    private void Exames( ) {
        int rand = new Random().nextInt( 100 ) + 1;
        if(rand >50)
            faz_exame = true;
        else
           faz_exame =  false;

        if (faz_exame == true) { // LOGICA É AO AVANCAR O DIA ELE VERIFICAR SO A DATA DE PAGAMENTO E EFETUAR O PAGAMENTO FACIL !
            data_exame.set( Calendar.DAY_OF_MONTH, (data_consulta.get( Calendar.DAY_OF_MONTH )) );
            data_consulta_resultados.set( Calendar.DAY_OF_MONTH, (data_consulta.get( Calendar.DAY_OF_MONTH ) + 7 ) );
            data_pagamento.set( Calendar.DAY_OF_MONTH, (data_consulta.get( Calendar.DAY_OF_MONTH ) + 7 ) );
        } else data_pagamento.set( Calendar.DAY_OF_MONTH, data_consulta.get( Calendar.DAY_OF_MONTH ) );
    }

    /*
    Metodo pagamento que faz os pagamentos
     */
    private void pagamento( ) {

        Valor_a_pagar = 0; // inicializa a 0
        if (faz_exame == true) { // verifica se fez um exame
            if (seg_med == true) { // verifica se tem seguro medico
                Valor_a_pagar = (valorConsulta * 0.4 + valorExame * 0.2); // aplica o valor a pagar
            } else if (idade >= 65) Valor_a_pagar = (valorConsulta * 0.1 + valorExame * 0.1); //verifica se tem mais que 65 anos e aplica o valor a pagar
            else Valor_a_pagar = valorConsulta + valorExame; // no caso que nao tenha seguro medico ou mais que 65 anos paga na totalidade
        } else {
            if (seg_med == true) { // caso nao faz exame nao precisa que o pagar
                Valor_a_pagar = (valorConsulta * 0.4);
            } else if (idade >= 65) Valor_a_pagar = (valorConsulta * 0.1);
            else Valor_a_pagar = valorConsulta;
        }
    }
/*
Getter para retornar variaveis privadas (Encapsulamento)
 */
    public Medicos getMedico( ) {
        return medico;
    }

    public Utentes getUtente( ) {
        return utente;
    }

    public Calendar getData_consulta( ) {
        return data_consulta;
    }

    public Calendar getData_exame( ) {
        return data_exame;
    }

    public Calendar getData_consulta_resultados( ) {
        return data_consulta_resultados;
    }

    public Calendar getData_pagamento( ) {
        return data_pagamento;
    }

    public boolean isFaz_exame( ) {
        return faz_exame;
    }
/*
Metodo toString que mostra ao utilizador da aplicaçao se ira fazer exame ou nao, as datas das consultas e o valor a pagar
 */
    @Override
    public String toString( ) {
        String text = "\n\n Medico: " + medico.getNum_medico_unico() +
                "\n Paciente: " + utente.getNome();

        if (faz_exame == false) {
            text = text + "\n\n Não vai fazer exame !" + "\n ";
            text = text + "\n Data da consulta: " + data_consulta.get( Calendar.DAY_OF_MONTH ) + "/" + data_consulta.get( Calendar.MONTH ) + "/" + data_consulta.get( Calendar.YEAR );
            text = text + "\n Data do pagamento: " + getData_pagamento().get( Calendar.DAY_OF_MONTH ) + "/" + getData_pagamento().get( Calendar.MONTH ) + "/" + getData_pagamento().get( Calendar.YEAR );
        } else {
            text = text + "\n\n Vai fazer exame !" + "\n ";
            text = text + "\n Data da consulta: " + data_consulta.get( Calendar.DAY_OF_MONTH ) + "/" + data_consulta.get( Calendar.MONTH ) + "/" + data_consulta.get( Calendar.YEAR );
            text = text + "\n Data do exame: " + data_exame.get( Calendar.DAY_OF_MONTH ) + "/" + data_exame.get( Calendar.MONTH ) + "/" + data_exame.get( Calendar.YEAR );
            text = text + "\n Data da consulta de resultados: " + getData_consulta_resultados().get( Calendar.DAY_OF_MONTH ) + "/" + data_consulta_resultados.get( Calendar.MONTH ) + "/" + getData_consulta_resultados().get( Calendar.YEAR );
            text = text + "\n Data do pagamento: " + getData_pagamento().get( Calendar.DAY_OF_MONTH ) + "/" + getData_pagamento().get( Calendar.MONTH ) + "/" + getData_pagamento().get( Calendar.YEAR );
        }
        text = text + "\n\n Valor a pagar: " + Valor_a_pagar + " € \n\n";

        return text;
    }
}