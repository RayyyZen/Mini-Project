#include "arbre.h"

pArbre constructeurArbre(){
    pArbre parbre;
    parbre.etu=NULL;
    parbre.fg=NULL;
    parbre.fd=NULL;
    return parbre;
}