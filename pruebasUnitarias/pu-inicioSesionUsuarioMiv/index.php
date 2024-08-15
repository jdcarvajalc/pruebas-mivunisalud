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

$loginMessage = "";

// Verificar si se envió el formulario de inicio de sesión
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Obtener los valores del formulario
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Preparar la consulta SQL
    $sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("ss", $username, $password);
    $stmt->execute();
    $result = $stmt->get_result();

    // Verificar si se encontró un usuario
    if ($result->num_rows > 0) {
        // Usuario encontrado, iniciar sesión
        echo "<script>alert('¡Inicio de sesión exitoso!');</script>";
    } else {
        // Credenciales incorrectas
        echo "<script>alert('Credenciales incorrectas. Inténtalo de nuevo.');</script>";
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
    <title>Inicio de Sesión</title>
</head>

<body>
    <h1>Iniciar Sesión</h1>
    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        Username: <input type="text" name="username" required><br>
        Password: <input type="password" name="password" required><br>
        <input type="submit" name="submit" value="Iniciar Sesión">
    </form>
</body>

</html>