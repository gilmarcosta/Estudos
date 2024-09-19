function carregar(){
    var msg = window.document.getElementById('msg')
    var img = window.document.getElementById('imagem') // id da tag imagem e nao da div
    var data = new Date()
    var hora = data.getHours()
    //var hora = 19
    msg.innerHTML = `<strong>Agora são ${hora} horas</strong>`
    if(hora >= 0 && hora <12){
        //BOM DIA
        img.src = 'img/manha.png' //img é a pasta dentro da raiz
        window.document.body.style.background = '#e2cd9f'
    }else if(hora >=12 && hora <= 18){
        //BOA TARDE
        img.src = 'img/tarde.png'
        window.document.body.style.background = '#b9846f'
    }else{
        //BOA NOITE
        img.src = 'img/noite.png'
        window.document.body.style.background = '#515154'
    }
}