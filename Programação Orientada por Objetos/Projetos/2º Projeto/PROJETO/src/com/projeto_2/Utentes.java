package com.projeto_2;

import java.util.Scanner;

public class Utentes implements Comparable<Utentes> {

    private String nome; // variavel para o nome
    private int idade;// variavel para a idade
    private int numero_de_utente;// variavel para o numero de utente

    private boolean seguro_medico;// variavel seguro medico verdadeiro ou false
    private double valor_pago;// variavel pra o valor pago
    private Scanner scan = new Scanner( System.in );

    /*
    Construtor da classe Utentes
     */
    public Utentes(String nome, int idade, int numero_de_utente, boolean seguro_medico) {

        this.nome = nome;
        this.idade = idade;
        this.numero_de_utente = numero_de_utente;
        this.seguro_medico = seguro_medico;
        valor_pago = 0;

    }

/*
Metodos getter para retornar as variaveis privadas (Encapsulamento)
 */
    public String getNome( ) {
        return nome;
    }

    public int getNumero_de_utente( ) {
        return numero_de_utente;
    }

    /*public void setNumero_de_utente(int numero_de_utente) {
        this.numero_de_utente = numero_de_utente;
    }*/

    public int getIdade( ) {
        return idade;
    }

    public boolean isSeguro_medico( ) {
        return seguro_medico;
    }


    public boolean getSeguro( ) {
        return seguro_medico;
    }
/*
Metodo equals para verificar se existe algum numero de utente igual
 */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        } else if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Utentes utentes = (Utentes) obj;
        return (numero_de_utente == utentes.getNumero_de_utente());
    }

    public double getValor_pago( ) {
        return valor_pago;
    }
/*
Metodo setValor_pago para encrementar o valor pago pelo utente
 */
    public void setValor_pago(double valor_pago) {
        this.valor_pago = this.valor_pago + valor_pago;
    }
/*
Metodo compareTo que atravez de  uma coleção ordena a lista de utentes
 */

    @Override
    public int compareTo(Utentes utentes) {
        if (this.valor_pago > utentes.getValor_pago()) {
            return -1;
        }
        if (this.valor_pago < utentes.getValor_pago()) {
            return 1;
        }
        return 0;
    }
/*
Metodo toString que mostra ao Utilizador da aplicação em texto as variaveis de cada utente
 */
    @Override
    public String toString( ) {
        return "\n - Nome - " + getNome() +
                "\n - Idade - " + getIdade() +
                "\n - Numero unico de utente - " + getNumero_de_utente() +
                "\n - Seguro medico - " + getSeguro() +
                "\n - Valor gasto - " + valor_pago;
    }
}


