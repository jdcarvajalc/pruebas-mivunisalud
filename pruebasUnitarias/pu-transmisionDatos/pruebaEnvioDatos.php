<?php
// No olvidar agregar ubicación e ID de dispositivo
$dato = $_POST['dato'];

$mysqli = new mysqli('localhost', 'root', '', 'pruebaEnvioDatos'); // Aquí se hace la conexión a la base de datos.

$sql1 = "INSERT into datos (id, dato) VALUES (NULL, '$dato')"; // Aquí se ingresa el valor recibido a la base de datos.

// Ejecutar la consulta y verificar si fue exitosa
if ($mysqli->query($sql1) === TRUE) {
    echo "Registro exitoso";
} else {
    echo "Error: " . $mysqli->error;
}

// Cerrar la conexión
$mysqli->close();
