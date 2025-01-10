let res= window.document.getElementById('res')  //declarar global
let num = window.document.getElementById('numero')
let lista = window.document.getElementById('flista')
let valores = []  //colchetes ao inves de chaves


let agora = new Date()
let hora = agora.getHours()

if(hora >= 6 && hora <= 12){
    window.document.body.style.background = '#9292f1'
}else{
    if(hora > 12 && hora <= 16){
        window.document.body.style.background = '#2424ac'
    }else{
        window.document.body.style.background = '#0e0e55'
    }
}

function isnumero(n){
    if(Number(n) >= 1 && Number(n) <= 100){
        return true
    }else{
        return false
    }
}

function inlista(n,l){
    if(l.indexOf(Number(n)) != -1){ // aula 15 sobre vetores explica
        return true
    }else{
        return false
    }
}

function adicionar(){
    
    if(isnumero(num.value) && !inlista(num.value, valores)){
        valores.push(Number(num.value))
        let item = window.document.createElement('option') //crases ''
        item.text = ` O numero ${num.value} foi adicionado.` //sem    
        lista.appendChild(item)
        res.innerHTML = ''
    }else{
        window.alert('Valor invalido ou já encontrado na lista.')
    }
    num.value =''
    num.focus()
}



function finalizar(){
    if(valores.length == 0){
        window.alert('Adicione valores antes de finalizar!')
    }else{
        resul.innerHTML = ` `
        let contador = 0
        let media = 0
        let maior = 0 //
        let menor = -1 //
        let soma = 0 //
        let quantidade = 0 //

        resul.innerHTML += `\u{1F449} `
        while(contador <= vetor.length-1){
            resul.innerHTML += `<strong> ${vetor[contador]} <strong> `
            contador ++;
        }

        resul.innerHTML += `<br>`

        contador = 0

        while(contador <= vetor.length-1){
            
            soma += Number(vetor[contador])
            if(vetor[contador] > maior){
                maior = vetor[contador]
            }
            if(vetor[contador] < menor || menor == -1){
                menor = vetor[contador]
            }
            contador ++;
        }
        quantidade = contador
        media = soma/quantidade

        if(contador == 0){
            resul.innerHTML += `Sem Valores`
        }else{
            resul.innerHTML += `<p>Ao todo temos ${quantidade} números cadastrados<p>`
            resul.innerHTML += `<p>O Maior valor informado foi ${maior}</p>`
            resul.innerHTML += `<p>O Menor valor informado foi ${menor}</p>`
            resul.innerHTML += `<p>Somando todos os valores temos ${soma}</p>`
            resul.innerHTML += `<p>A Média dos valores digitados é  ${media}</p>`
        }
    }
    /*
    ao todo temos x numeros cadastrados
    o maior valor informado foi x
    o menor valor informado foi x
    Somando todos os valores temos x
    a media dos valores digitados é 
    */

//resul.innerHTML += `  ${vetor[contador]}   `
}

