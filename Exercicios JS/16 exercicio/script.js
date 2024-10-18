let resposta = window.document.getElementById('res')  //declarar global
let n = window.document.getElementById('numero')
let vetor = []  //colchetes ao inves de chaves
let resul = window.document.getElementById('resultado')

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


function adicionar(){
    if(n.value.length==0){
        window.alert('Insira um valor!!')
    }else{
        let num = Number(n.value)
        if(num > 100 || num < 0){
            window.alert('Insira um valor de 0 a 100!!')
        }else{
            vetor += [num]
            let op = window.document.createElement('option') //crases ''
            op.text = innerHTML = ` O numero ${num} foi adicionado` //sem parenteses  
            res.appendChild(op)
            numero.text = ``
        }
    }
}



function finalizar(){
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

    /*
    ao todo temos x numeros cadastrados
    o maior valor informado foi x
    o menor valor informado foi x
    Somando todos os valores temos x
    a media dos valores digitados é 
    */

//resul.innerHTML += `  ${vetor[contador]}   `
}

