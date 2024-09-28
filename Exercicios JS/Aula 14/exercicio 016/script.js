
function calcular(){
    var numero = window.document.getElementById('numero')
    var fim = window.document.getElementById('fim')
    var passo = window.document.getElementById('passo')
    var saida = window.document.getElementById('res')
    res.innerHTML +=(`${numero}`)
    for(var cont=numero;cont<=fim;cont+=passo){
        res.innerHTML += `${cont} 👉`
    }
    res.innerHTML +=(`${cont}🏁`)
}