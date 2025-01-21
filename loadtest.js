import http from "k6/http";

export const options = {
  scenarios: {
    constant_request_rate: {
      executor: "constant-arrival-rate",
      rate: 50000,
      timeUnit: "1s",
      duration: "30s",
      preAllocatedVUs: 2000,
      maxVUs: 6000 
    }
  }
}

export default function () {
  http.get(`http://localhost:8000/api/orders`);
}
