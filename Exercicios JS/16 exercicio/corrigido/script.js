
let n = window.document.getElementById('numero')
let lista = window.document.getElementById('resultado')
let res = getElementById('res')
let vetor = []
function adicionar(){
    
    if(n.value.length==0){
        window.alert('Insira um valor!!')
    }else{
        let num = Number(n.value)
        if(num > 100 || num < 0){
            window.alert('Insira um valor de 0 a 100!!')
        }else{
            vetor = [num]
            let option = document.createElement(option)
                option.appendChild(vetor)
            res.appendChild()
        }
    }
}

function finalizar(){
    res = innerHTML(`${vetor}`)
    let contador = 0
    while(contador < vetor.length-1){
        res += innerHTML(`${vetor[contador]}`)
        contador += 1;
    }
}

