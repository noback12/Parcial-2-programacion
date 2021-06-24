#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>


using namespace std;


class COMPONENTE {
    public :
        char NOM[20] ;
        COMPONENTE * SIG ;

};

class DOLENCIA {
        public :
            char NOM[20] ;
            DOLENCIA * SIG ;
};

class MEDICINA {
        public :
            char NOM[20] ;
            COMPONENTE * PCOM ;
            DOLENCIA * PDOL ;
            MEDICINA * SIG ;
};

class VADEMECUM {
        private :
            MEDICINA * ORIGEN ;

        public :
            int CHEAPER (char *, const LISTA_DE_PRECIOS &) ;
};


class LABORATORIO {
    public :
        char NOM[20] ;
        int COSTO ;
        LABORATORIO * SIG ;
};


class COMPONENTE_QUIMICO {
    public :
        char NOM[20] ;
        LABORATORIO * PLAB ;
        COMPONENTE_QUIMICO * SIG ;
};

class LISTA_DE_PRECIOS {
    private :
        COMPONENTE_QUIMICO * COMPORIGEN ;
    public :
        friend int VADEMECUM::CHEAPER (char *, const LISTA_DE_PRECIOS &) ;
         COMPONENTE_QUIMICO * accederInicio()  ;
};





//MANDA DESDE ACAAAAAA y CHEQUIA QUE NO TE HAYAN QUEDADO NADA EN PRIVADO



COMPONENTE_QUIMICO * LISTA_DE_PRECIOS::accederInicio ()  {
        COMPONENTE_QUIMICO * devolver ;
        devolver = COMPORIGEN;
    return  devolver;

}


friend int VADEMECUM::CHEAPER(char * dolCon , const LISTA_DE_PRECIOS & listaPrecios){

        //para encontrar la medicina que trata dicha dolencia

        MEDICINA * recMed ;
        COMPONENTE * recCom;
        DOLENCIA * recDol;
        recMed = ORIGEN ;


        //para encontrar el precio mas barato
        COMPONENTE_QUIMICO * recComPrecio ;
        char medfinal [20];
        LABORATORIO * recLab ;
        int precioDelLab = 0;
        int precioParcial = 0;
        int precioFinal = 0 ;



        //entro en las distintas medicinas para ver si tratan esas dolencias
        while(recMed){
            recDol = recMed->PDOL ;

            //recorro hasta encontrarla o terminar la lista de dolencias
            while(strcmp(recDol->NOM,dolCon)  &&  recDol ){
                recDol = recDol->SIG;
            }
            //Si coinciden los nombres es porque encontre una medicina que trata esa dolencia y necesito saber todos los componentes de esa medicina para calcular el precio
            if ( !strcmp(recDol->NOM,dolCon)){
                recCom = recMed->PCOM ;

                //Empiezo a recorrer los componentes de la medicina ; hice un metodo a lista precio porque el atributo es privado
                while (recCom){
                    recComPrecio = listaPrecios.accederInicio() ;
                        //busco cada componente en la lista de precios
                        while (strcmp (recComPrecio->NOM ,recCom->NOM) && recComPrecio ){

                                recComPrecio = recComPrecio->SIG ;
                        }
                        //Si lo encontre , busco el laboratorio mas barato que produce ese componente
                        if ( !strcmp (recComPrecio->NOM ,recCom->NOM) ){

                            recLab = recComPrecio ->PLAB ;
                            precioDelLab = recLab->COSTO;
                            //asigne el primer precio y recorro toda la lista buscando uno mas barato
                            while (recLab){
                                //me quedo con el laboratorio mas barato
                                if (recLab->COSTO < precioDelLab){
                                    precioDelLab = recLab->COSTO;
                                }

                                recLab =recLab->SIG;
                            }
                            //Una vez encontrado el laboratorio mas barato , sumo ese precio al precio del medicamento hasta que no queden mas componentes de ese medicamento
                            precioParcial = precioParcial + precioDelLab ;
                        }

                    recCom = recCom->SIG;
                }

                //si sale mas barato o es el primer precio lo asigno
                if (precioParcial<precioFinal || precioFinal == 0){
                    precioFinal = precioParcial ;
                }

                //Pongo mi precio parcial en 0 para empezar a comparar el nuevo medicamento mas economico con el resto de la lista que trate la dolencia
                precioParcial = 0 ;

            }

            recMed = recMed->SIG;
        }



        return  precioFinal;
}




