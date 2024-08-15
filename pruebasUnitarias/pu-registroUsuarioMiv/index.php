<?php
// Datos de conexión a la base de datos
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dbfarmacia";

// Crear conexión
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexión
if ($conn->connect_error) {
    die("Error al conectar a la base de datos: " . $conn->connect_error);
}

// Verificar si se envió el formulario de registro
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Obtener los valores del formulario
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Preparar la consulta SQL
    $sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("ss", $username, $password);

    // Ejecutar la consulta
    if ($stmt->execute()) {
        echo "Usuario registrado exitosamente";
    } else {
        echo "Error al registrar el usuario: " . $stmt->error;
    }

    // Cerrar la declaración
    $stmt->close();
}

// Cerrar la conexión
$conn->close();
?>

<!DOCTYPE html>
<html>

<head>
    <title>Registro de Usuario</title>
</head>

<body>
    <h1>Registro de Usuario</h1>
    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" name="submit" value="Registrar">
    </form>
</body>

</html>