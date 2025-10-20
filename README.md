# CrowCpp Authentication Template Starter

A ready-to-use **CrowCpp** template for building authenticated REST APIs in C++. This starter project comes pre-configured with user authentication, JWT tokens, Swagger UI documentation, and Docker support - get your API up and running in minutes!

## Quick Start

### Prerequisites

- CMake (3.10+)
- C++17 compiler
- Docker (Optimized But Optional)

### Run with Docker

```bash
docker build -t crow-auth-starter .
docker run -p 8080:8080 crow-auth-starter
```

### Run Locally

```bash
git clone <your-repo-url>
cd crow_auth_project
mkdir build && cd build
cmake ..
make
./crow_auth_project
```

Visit `http://localhost:8080/docs` for interactive API documentation!

## Features

### Authentication Ready

- User registration and login endpoints
- JWT-based authentication
- Secure password hashing
- Protected routes with middleware

### Swagger UI Integration

- Auto-generated API documentation
- Interactive endpoint testing
- OpenAPI 3.0 specification
- Accessible at `/docs` endpoint

### Docker Integration

- Multi-stage Dockerfile for optimized builds
- Development and production configurations
- Easy deployment and scaling

### JSON API

- RESTful endpoints with JSON responses
- Request validation and parsing
- Structured error handling

### Clean Architecture

- Modular design with routes, services, and models
- Separation of concerns
- Extensible for additional features

## 📁 Project Structure

```
crow_auth_project/
├── include/                 # Header files
│   ├── models/user.hpp     # User data model
│   ├── routes/             # API route handlers
│   │   ├── auth_routes.hpp
│   │   └── profile_routes.hpp
│   ├── services/           # Business logic
│   │   ├── jwt_service.hpp
│   │   └── user_service.hpp
│   └── utils/              # Utilities
│       ├── CrowSwaggerLocal.hpp
│       ├── crypto_utils.hpp
│       └── validation_utils.hpp
├── src/                    # Implementation files
├── Dockerfile              # Container configuration
├── CMakeLists.txt          # Build system
├── users.json              # Sample data
└── .env.example            # Environment template
```

## 🔧 API Endpoints

| Method | Endpoint | Description | Auth Required |
|--------|----------|-------------|---------------|
| POST | `/auth/register` | Register new user | ❌ |
| POST | `/auth/login` | User login | ❌ |
| GET | `/profile` | Get user profile | ✅ |
| PUT | `/profile` | Update profile | ✅ |

## Technologies

- **CrowCpp** - Modern C++ web framework
- **JWT** - Token-based authentication
- **OpenSSL** - Cryptography
- **nlohmann/json** - JSON handling
- **Docker** - Containerization
- **Swagger/OpenAPI** - API documentation

## Use Cases

Perfect for:

- Building microservices in C++
- Prototyping authenticated APIs
- Learning CrowCpp framework
- Starting new projects quickly

## 📖 Documentation

- API docs available at `/docs` when running
- Code comments for implementation details
- Sample requests in Swagger UI

---

**Ready to build your next API?** This template provides everything you need to start developing authenticated services with CrowCpp. Fork, customize, and deploy! 
