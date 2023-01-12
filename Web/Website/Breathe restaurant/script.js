

/* ------------------- toggle navbar -------------------- */
const navToggler = document.querySelector(".nav-toggler");
navToggler.addEventListener("click", toggleNav);

function toggleNav(){
    document.querySelector(".nav").classlight.toggle("open");
    
}