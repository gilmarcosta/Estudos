function verificar(){
    
var data = new Date()
var ano = data.getFullYear()
var fano = window.document.getElementById('ano')
var res = window.document.querySelector('div#resultado')
if(fano.value.length == 0 || Number(fano.value) > ano){
    window.alert('[ERRO] Verifique os dados e tente novamente!!')
}else{
    var fsex = window.document.getElementsByName('radsexo')
    var idade = ano - Number(fano.value)
    var genero = ''
    var img = document.createElement('img')
    img.setAttribute('id','foto')
    if(fsex[0].checked){
        genero = 'Homem'
        if(idade >= 0 && idade <= 6){
            //bebe
            img.setAttribute('src','img/bebeh.png')
        }else if(idade <= 14){
            //crianca
            img.setAttribute('src','img/menino.png')
        }else if(idade <= 50 ){
            //jovem
            img.setAttribute('src','img/jovemh.png')
        }else{
            //idoso
            img.setAttribute('src','img/idoso.png')
        }
    }else if(fsex[1].checked){
        genero = 'Mulher'
        if(idade >= 0 && idade <= 6){
            //bebe
            img.setAttribute('src','img/bebem.png')
        }else if(idade <= 14){
            //crianca
            img.setAttribute('src','img/menina.png')
        }else if(idade <= 50 ){
            //jovem
            img.setAttribute('src','img/jovemm.png')
        }else{
            //idoso
            img.setAttribute('src','img/idosa.png')
        }
    }
    res.style.textAlign = 'center'
    res.innerHTML = `<p>Detectamos ${genero} com ${idade} anos.</p>`
    res.appendChild(img)  
}


}