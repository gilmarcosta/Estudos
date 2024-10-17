let resposta = window.document.getElementById('res')  //declarar global
let n = window.document.getElementById('numero')
let vetor = []  //colchetes ao inves de chaves
let resul = window.document.getElementById('resultado')



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
        }
    }
}



function finalizar(){
    let contador = 0
    while(contador <= vetor.length-1){
        //window.alert(`${vetor[contador]}`)
        resul.innerHTML += `  ${vetor[contador]}   `
        contador ++;
    }
}

