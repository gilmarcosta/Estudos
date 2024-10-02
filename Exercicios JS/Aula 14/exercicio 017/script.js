function Calcular(){

    let num = window.document.getElementById('valor')
    let resposta = window.document.getElementById('res')


    if(num.value.length == 0){
        window.alert('Insira algum valor!!')
    }else{
        window.alert('Tudo ok')
        resposta.innerHTML = ''
        let n = Number(num.value)
        let cont = 0 

        while(cont <= 10){
            let re = window.document.createElement('option')
            re.text = innerHTML = ` ${n} X ${cont} = ${n*cont}`
            res.appendChild(re)
            cont ++
        }

    }

}