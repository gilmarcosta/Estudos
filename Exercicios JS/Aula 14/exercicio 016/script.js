
function calcular(){
    //essa parte pega os valores do input
    let numero = window.document.getElementById('numero')
    let fim = window.document.getElementById('final')
    let passo = window.document.getElementById('passo')
    
    
    if(numero.value.length == 0 || fim.value.length == 0 || passo.value.length == 0){
        window.alert('Faltam dados!')
    }else{
        //essa parte faz o casting dos valores pego acima
        let i = Number(numero.value)  // pois o valor e considerado como texto, logo e necessario fazer o casting
        let f = Number(fim.value)
        let p = Number(passo.value)
        let saida = window.document.getElementById('res')
        saida.innerHTML = (` `) //para limpar a tela (div res) 

        if(p <= 0){//caso o usuario digite o valor 0
            saida.innerHTML += `Passo menor ou igual a 0 será considerado como 1 <br><br>`
            p = 1
        }
        saida.innerHTML += (`Resultado: <br>`)

        if(i < f){//contagem progressiva
            for(let cont=i ; cont <= f ; cont += p){
                saida.innerHTML += ` \u{1F449} ${cont} `
            }
        }else if(i > f){//contagem regressiva
            for(let cont=i ; cont >= f ; cont -= p){
                saida.innerHTML += ` \u{1F449} ${cont} `
            }
        }else{
            saida.innerHTML += ` \u{1F449} ${i} ` // se o inicio e fim for o mesmo
        }
        saida.innerHTML +=(`\u{1F3C1}`)
    }

}