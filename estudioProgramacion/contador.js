let total = 0, count = 1; 
let texto = "mi textualidad con una tabulación.\t Mi textualidad con salto de línea.\n Mi textualidad con una barra invertida.\\ Mi textualidad con comillas dobles.\" Mi textualidad con comillas simples.\'";
let mitad = 100
let dividendo = 2
while (count <= 10) {
    total += count
    count += 1
    console.log(count, total)
}
console.log(texto)

console.log(`la mitad de 100 es ${mitad / dividendo}`)
console.log(false ? "es verdadero" : "es falso")